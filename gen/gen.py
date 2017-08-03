#!/usr/bin/env python2
# coding=utf-8
"""Generate hangover syscalls"""

import argparse
import fnmatch
import os
import re
import shutil
import subprocess
import sys

__copyright__ = "Copyright 2017, André Hentschel"

APIKEYWORD = "WINBASEAPI"
MISSINGFUNCS = []
POINTERS = []

def type_is_ptr(typ):
    global POINTERS
    if typ == "LPARAM":
        return False
    if typ == "HWND" or typ == "HANDLE":
        return True
    if typ == "HICON" or typ == "HCURSOR" or typ == "HBITMAP" or typ == "HDC" or typ == "HBRUSH":
        return True
    if typ == "HKL" or typ == "HMENU" or typ == "HMONITOR":
        return True
    if typ == "HACCEL" or typ == "HDWP" or typ == "HWINSTA" or typ == "HDESK":
        return True
    if typ == "HDEVNOTIFY" or typ == "HPOWERNOTIFY":
        return True
    if typ == "HHOOK" or typ == "HWINEVENTHOOK":
        return True
    if typ == "HINSTANCE" or typ == "HMODULE":
        return True
    if typ == "HRAWINPUT" or typ == "PRAWINPUT":
        return True
    if typ == "HTASK" or typ == "HFONT" or typ == "HRGN":
        return True
    if typ == "HDDEDATA" or typ == "HMETAFILE":
        return True
    if typ == "PVOID" or typ == "PUINT" or typ == "PULONG":
        return True
    if typ.endswith("PROC") or typ.endswith("PROCA") or typ.endswith("PROCW"):
        return True
    if typ.endswith("PROCEXA") or typ.endswith("PROCEXW"):
        return True
    if typ.endswith("PTRUSTEEA") or typ.endswith("PTRUSTEEW"):
        return True
    if typ == "PTRUSTEEA" or typ == "PTRUSTEEW":
        return True
    if typ.endswith("FN_PROGRESS"):
        return True
    if typ.endswith("SAFER_LEVEL_HANDLE"):
        return True
    if typ.endswith("PEXPLICIT_ACCESSW"):
        return True
    if typ.endswith("PEXPLICIT_ACCESSA"):
        return True
    if typ.endswith("PACCESS_MASK"):
        return True
    if typ.endswith("POBJECTS_AND_SID"):
        return True
    if typ.endswith("POBJECTS_AND_NAME_W"):
        return True
    if typ.endswith("POBJECTS_AND_NAME_A"):
        return True
    if typ.endswith("PACL"):
        return True
    if typ.endswith("PUCHAR"):
        return True
    if typ.endswith("PULONG"):
        return True
    if typ.endswith("PSECURITY_DESCRIPTOR"):
        return True
    if typ.endswith("LPDWORD"):
        return True
    if typ.endswith("LPBOOL"):
        return True
    if typ.endswith("LPCSTR"):
        return True
    if typ.endswith("LPCWSTR"):
        return True
    if typ.endswith("LPWSTR"):
        return True
    if typ.endswith("LPSTR"):
        return True
    if typ.endswith("PSID"):
        return True
    if typ.endswith("PSID_NAME_USE"):
        return True
    if typ in POINTERS:
        return True
    if typ.startswith("LP"):
        return True
    return False

def func_ret(curfunc):
    return curfunc.replace(APIKEYWORD, "").strip().split()[0]

def func_ret_is_ptr(curfunc):
    ret = func_ret(curfunc)
    if type_is_ptr(ret):
        return True
    return False

def func_ret_is_void(curfunc):
    ret = func_ret(curfunc)
    if ret == "void" or ret == "VOID":
        return True
    return False

def func_name(curfunc):
    rgx = re.search(r"WINAPI\s+(.*)\s*\(", curfunc)
    return rgx.group(1).rsplit(None, 1)[-1] # get the last word

def func_arg(curfunc, argn):
    rgx = re.search(r"\((.*)\)", curfunc)
    args = rgx.group(1).split(',')
    arg = args[argn]
    return arg.strip()

def func_arg_is_ptr(curfunc, argn):
    arg = func_arg(curfunc, argn)
    argname = arg.rsplit(None, 1)[-1].replace('*', '')
    argtype = arg.replace(argname, '').strip()
    if '*' in argtype:
        return True
    if type_is_ptr(argtype):
        return True
    return False

def func_argname(curfunc, argn):
    arg = func_arg(curfunc, argn)
    argname = arg.rsplit(None, 1)[-1].replace('*', '')
    return argname.strip()

def func_argc(curfunc):
    rgx = re.search(r"\((.*)\)", curfunc)
    cnt = rgx.group(1).count(',')
    if not cnt and not rgx.group(1).count(' '):
        return 0
    return cnt + 1

def normalize_function(curfunc):
    normfunc = curfunc.replace("{", "").replace("DECLSPEC_HOTPATCH", "")
    normfunc = normfunc.replace(APIKEYWORD, "")
    normfunc = normfunc.strip()
    normfunc = re.sub(r"\s+", " ", normfunc)
    normfunc = re.sub(r"\).*\/\*.*", ")", normfunc)
    normfunc = normfunc.replace("( ", "(").replace(" )", ")")
    return normfunc.strip()

def gen_struct(curfunc):
    struct = "struct qemu_" + func_name(curfunc) + "\n{\n    struct qemu_syscall super;\n"
    if not func_argc(curfunc):
        return struct + "};"
    for x in xrange(func_argc(curfunc)):
        struct = struct + "    uint64_t " + func_argname(curfunc, x) + ";\n"
        #print func_arg(curfunc, x) + " <<<---- " + str(func_arg_is_ptr(curfunc, x))
    return struct + "};"

def gen_guest(curfunc):
    fname = func_name(curfunc)
    guest = APIKEYWORD + " " + curfunc + "\n{\n    struct qemu_" + fname + " call;\n"
    guest = guest + "    call.super.id = QEMU_SYSCALL_ID(CALL_" + fname.upper() + ");\n"
    for x in xrange(func_argc(curfunc)):
        argname = func_argname(curfunc, x)
        guest = guest + "    call." + argname + " = (uint64_t)" + argname + ";\n"
    guest = guest + "\n    qemu_syscall(&call.super);"
    if func_ret_is_ptr(curfunc):
        guest = guest + "\n\n    return (" + func_ret(curfunc) + ")call.super.iret;\n"
    elif func_ret_is_void(curfunc):
        guest = guest + "\n"
    else:
        guest = guest + "\n\n    return call.super.iret;\n"
    return guest + "}"

def gen_host(curfunc):
    fname = func_name(curfunc)
    if fname in MISSINGFUNCS:
        host = "/* TODO: Add " + fname + " to Wine headers? */\n"
        host = host + "extern " + curfunc + ";\n"
    else:
        host = ""
    host = host + "void qemu_" + fname + "(struct qemu_syscall *call)\n{\n"
    host = host + "    struct qemu_" + fname + " *c = (struct qemu_" + fname + " *)call;\n"
    host = host + "    WINE_FIXME(\"Unverified!\\n\");\n"
    if func_ret_is_void(curfunc):
        host = host + "    " + fname + "("
    elif func_ret_is_ptr(curfunc):
        host = host + "    c->super.iret = (uint64_t)" + fname + "("
    else:
        host = host + "    c->super.iret = " + fname + "("
    argc = func_argc(curfunc)
    if not argc:
        return host + ");\n}"
    for x in xrange(argc):
        argname = func_argname(curfunc, x)
        if func_arg_is_ptr(curfunc, x):
            host = host + "QEMU_G2H(c->" + argname + ")"
        else:
            host = host + "c->" + argname
        if x != argc - 1:
            host = host + ", "
    return host + ");\n}"

def gen_syscall_wrapper(curfunc, nfile):
    normfunc = normalize_function(curfunc)
    output = gen_struct(normfunc) + "\n\n#ifdef QEMU_DLL_GUEST\n\n" + gen_guest(normfunc)
    output = output + "\n\n#else\n\n" + gen_host(normfunc) + "\n\n#endif\n\n"
    nfile.write(output)
    return func_name(normfunc)

def do_functions(dllname, cfile):
    badcontent = ("(WINAPI", "static", ";", "DllMain", "...", "va_list", "WndProc")
    names = []
    curfunc = ""
    lastline = ""
    infunc = False
    ffile = open(cfile, "r")
    nfile = open(cfile + "2", "w")
    nfile.write("/*\n")
    nfile.write(" * Copyright 2017 André Hentschel\n")
    nfile.write(" *\n")
    nfile.write(" * This library is free software; you can redistribute it and/or\n")
    nfile.write(" * modify it under the terms of the GNU Lesser General Public\n")
    nfile.write(" * License as published by the Free Software Foundation; either\n")
    nfile.write(" * version 2.1 of the License, or (at your option) any later version.\n")
    nfile.write(" *\n")
    nfile.write(" * This library is distributed in the hope that it will be useful,\n")
    nfile.write(" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n")
    nfile.write(" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n")
    nfile.write(" * Lesser General Public License for more details.\n")
    nfile.write(" *\n")
    nfile.write(" * You should have received a copy of the GNU Lesser General Public\n")
    nfile.write(" * License along with this library; if not, write to the Free Software\n")
    nfile.write(" * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA\n")
    nfile.write(" */\n")
    nfile.write("\n")
    nfile.write("/* NOTE: The guest side uses mingw's headers. The host side uses Wine's headers. */\n")
    nfile.write("\n")
    nfile.write("#include <windows.h>\n")
    nfile.write("#include <windows.h>\n")
    nfile.write("#include <windows.h>\n")
    nfile.write("#include <stdio.h>\n")
    nfile.write("#include <winternl.h>\n")
    nfile.write("#include <ddk/ntddk.h>\n")
    nfile.write("\n")
    nfile.write("#include \"windows-user-services.h\"\n")
    nfile.write("#include \"dll_list.h\"\n")
    nfile.write("#include \"" + dllname + ".h\"\n")
    nfile.write("\n")
    nfile.write("#ifndef QEMU_DLL_GUEST\n")
    nfile.write("#include <wine/debug.h>\n")
    nfile.write("WINE_DEFAULT_DEBUG_CHANNEL(qemu_" + dllname + ");\n")
    nfile.write("#endif\n\n\n")
    for line in ffile:
        line = re.sub(r"\/\*.*\*\/", "", line)
        if "WINAPI" in line and not any(bc in line for bc in badcontent):
            infunc = True
            curfunc = ""
        if infunc:
            if line.strip().startswith("WINAPI"):
                curfunc = lastline.strip() + " " + line.strip()
            else:
                curfunc = curfunc + " " + line.strip()
        else:
            lastline = line
        if ")" in line:
            if infunc:
                names.append(gen_syscall_wrapper(curfunc, nfile))
            infunc = False
    nfile.close()
    ffile.close()
    os.rename(cfile + "2", cfile)
    return names


def meta_header_funcs(dllname, names):
    orig = []
    phase = 0
    hfile = open(dllname + ".h", "r")
    for line in hfile:
        if line.startswith("#ifndef QEMU_DLL_GUEST"):
            phase = 1
            continue
        if phase == 1 and line.startswith("void"):
            phase = 2
        if phase == 2 and not line.startswith("void"):
            phase = 3
            break
        if phase == 2:
            orig.append(line)
    hfile.close()
    for n in names:
        proto = "void qemu_" + n + "(struct qemu_syscall *call);\n"
        if proto in orig:
            print "Warning: Prototype for " + n + " already in header!"
        else:
            orig.append(proto)
    modified = sorted(orig, key=lambda o: o.lower())

    phase = 0
    hfile = open(dllname + ".h", "r")
    nfile = open(dllname + ".h2", "w")
    for line in hfile:
        if phase == 0:
            nfile.write(line)
            if line.startswith("#ifndef QEMU_DLL_GUEST"):
                phase = 1
            continue
        if phase == 1 and line.startswith("void"):
            phase = 2
            continue
        if phase == 2 and not line.startswith("void"):
            for m in modified:
                nfile.write(m)
            nfile.write(line)
            phase = 3
            continue
        if phase == 1 or phase == 3:
            nfile.write(line)
            continue
    nfile.close()
    hfile.close()
    os.rename(dllname + ".h2", dllname + ".h")

def meta_header(dllname, names):
    orig = []
    phase = 0
    hfile = open(dllname + ".h", "r")
    for line in hfile:
        if line.startswith("enum " + dllname + "_calls"):
            phase = 1
            continue
        if phase == 1 and line.startswith("{"):
            phase = 2
            continue
        if phase == 2 and "}" in line:
            phase = 3
            break
        if phase == 2:
            orig.append(line.replace(" = 0", ""))
    hfile.close()
    for n in names:
        call = "    CALL_" + n.upper() + ",\n"
        if call in orig:
            print "Warning: Enum CALL_" + n.upper() + " already in header!"
        else:
            orig.append(call)
    modified = sorted(orig, key=lambda o: o.lower())

    phase = 0
    hfile = open(dllname + ".h", "r")
    nfile = open(dllname + ".h2", "w")
    for line in hfile:
        if phase == 0:
            nfile.write(line)
            if line.startswith("enum " + dllname + "_calls"):
                phase = 1
            continue
        if phase == 1 and line.startswith("{"):
            nfile.write(line)
            phase = 2
            continue
        if phase == 2 and "}" in line:
            first = True
            for m in modified:
                #m = m.replace(" = 0", "")
                if first:
                    nfile.write(m.replace(",", " = 0,"))
                    first = False
                else:
                    nfile.write(m)
            nfile.write(line)
            phase = 3
            continue
        if phase == 3:
            nfile.write(line)
            continue
    nfile.close()
    hfile.close()
    os.rename(dllname + ".h2", dllname + ".h")

def meta_def(dllname, names):
    orig = []
    phase = 0
    dfile = open(dllname + ".def", "r")
    for line in dfile:
        if phase == 0 and line.startswith("EXPORTS"):
            phase = 1
            continue
        if phase == 1:
            orig.append(line)
    dfile.close()
    for n in names:
        defline = "  " + n + "\n"
        if defline in orig:
            print "Warning: Def " + n + " already in .def file!"
        else:
            orig.append(defline)
    modified = sorted(orig, key=lambda o: o.lower())

    dfile = open(dllname + ".def", "r")
    nfile = open(dllname + ".def2", "w")
    for line in dfile:
        nfile.write(line)
        if line.startswith("EXPORTS"):
            break
    for m in modified:
        nfile.write(m.replace(',', ''))
    nfile.close()
    dfile.close()
    os.rename(dllname + ".def2", dllname + ".def")

def meta_main(dllname, names):
    orig = []
    phase = 0
    cfile = open("main.c", "r")
    for line in cfile:
        if line.startswith("static const syscall_handler dll_functions"):
            phase = 1
            continue
        if phase == 1 and line.startswith("{"):
            phase = 2
            continue
        if phase == 2 and "}" in line:
            phase = 3
            break
        if phase == 2:
            orig.append(line)
    cfile.close()
    for n in names:
        fptr = "    qemu_" + n + ",\n"
        if fptr in orig:
            print "Warning: Function pointer qemu_" + n + " already in main.c!"
        else:
            orig.append(fptr)
    modified = sorted(orig, key=lambda o: o.lower())

    phase = 0
    cfile = open("main.c", "r")
    nfile = open("main.c2", "w")
    for line in cfile:
        if phase == 0:
            nfile.write(line)
            if line.startswith("static const syscall_handler dll_functions"):
                phase = 1
            continue
        if phase == 1 and line.startswith("{"):
            nfile.write(line)
            phase = 2
            continue
        if phase == 2 and "}" in line:
            for m in modified:
                nfile.write(m)
            nfile.write(line)
            phase = 3
            continue
        if phase == 3:
            nfile.write(line)
            continue
    nfile.close()
    cfile.close()
    os.rename("main.c2", "main.c")

def meta_makefile(dllname, cfile):
    sguest = dllname + ".dll: "
    shost = "qemu_" + dllname + ".dll.so: "
    mfile = open("Makefile", "r")
    nfile = open("Filemake", "w")
    for line in mfile:
        if line.startswith(sguest):
            obj = cfile.replace(".c", "_g.o")
            deps = line[len(sguest):].split()
            if obj in deps:
                print "Warning: Object file " + obj + " already in Makefile!"
            else:
                deps.append(obj)
            modified = sorted(deps, key=lambda d: d.lower())
            nfile.write(sguest + " ".join(modified) + "\n")
            continue
        if line.startswith(shost):
            obj = cfile.replace(".c", "_h.o")
            deps = line[len(shost):].split()
            if obj in deps:
                print "Warning: Object file " + obj + " already in Makefile!"
            else:
                deps.append(obj)
            modified = sorted(deps, key=lambda d: d.lower())
            nfile.write(shost + " ".join(modified) + "\n")
            continue
        nfile.write(line)
    nfile.close()
    mfile.close()
    os.rename("Filemake", "Makefile")

def do_meta(dllname, cfile, names):
    meta_main(dllname, names)
    meta_def(dllname, names)
    meta_header(dllname, names)
    meta_header_funcs(dllname, names)
    meta_makefile(dllname, cfile)

def make_parse(output):
    global MISSINGFUNCS
    global POINTERS
    txtfile = open(output, "r")
    for line in txtfile:
        if "error:" in line:
            print line.strip()
        elif "warning: implicit declaration of function" in line:
            rgx = re.search(r"warning: implicit declaration of function (.*)", line)
            if not rgx:
                continue
            missing = rgx.group(1).split()[0]
            missing = missing.replace("‘", "").replace("’", "").strip()
            if missing not in MISSINGFUNCS:
                MISSINGFUNCS.append(missing)
        elif "note: expected" in line:
            rgx = re.search(r"note: expected (.*) but argument is of type (.*)", line)
            if not rgx:
                continue
            if rgx.group(2) == "‘uint64_t {aka long unsigned int}’":
                ptr = rgx.group(1).split()[0]
                ptr = ptr.replace("‘", "").replace("’", "").strip()
                if ptr not in POINTERS:
                    POINTERS.append(ptr)
    txtfile.close()

def do_makeoutput_all(dllname):
    subprocess.Popen("rm *_h.o", shell=True).wait()
    subprocess.Popen("touch /tmp/gen.py.txt", shell=True).wait()
    subprocess.Popen("make qemu_" + dllname + ".dll.so 2>> /tmp/gen.py.txt", shell=True).wait()
    make_parse("/tmp/gen.py.txt")
    print "\nif typ == \"" + "\" or typ == \"".join(POINTERS) + "\":"

def do_makeoutput_single(cfile):
    obj = cfile.replace(".c", "") + "_h.o"
    #os.remove(obj)
    subprocess.Popen("make " + obj + " 2> /tmp/gen.py.txt", shell=True).wait()
    make_parse("/tmp/gen.py.txt")

def do_makeoutput(dllname, cfile):
    if True:
        do_makeoutput_single(cfile)
    else:
        do_makeoutput_all(dllname)

PARSER = argparse.ArgumentParser(description='Generate hangover syscalls')
PARSER.add_argument('cfile', nargs='?', help='a single C file')
PARSER.add_argument('dllname', nargs='?', help='name of the dll')

ARGS = PARSER.parse_args()

try:
    subprocess.check_call("git rev-parse --show-toplevel > /dev/null", shell=True)
except subprocess.CalledProcessError:
    print "You need to be in a Git repository"
    sys.exit(1)

if ARGS.cfile and ARGS.dllname:
    names = do_functions(ARGS.dllname, ARGS.cfile)
    do_meta(ARGS.dllname, ARGS.cfile, names)
    do_makeoutput(ARGS.dllname, ARGS.cfile)
    do_functions(ARGS.dllname, ARGS.cfile)
