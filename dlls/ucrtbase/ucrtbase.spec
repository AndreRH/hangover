# MS VC++2010 runtime library

# @ thiscall -arch=win32 ??0?$_SpinWait@$00@details@Concurrency@@QAE@P6AXXZ@Z(ptr ptr) SpinWait_ctor_yield
# @ cdecl -arch=win64 ??0?$_SpinWait@$00@details@Concurrency@@QEAA@P6AXXZ@Z(ptr ptr) SpinWait_ctor_yield
# @ thiscall -arch=win32 ??0?$_SpinWait@$0A@@details@Concurrency@@QAE@P6AXXZ@Z(ptr ptr) SpinWait_ctor
# @ cdecl -arch=win64 ??0?$_SpinWait@$0A@@details@Concurrency@@QEAA@P6AXXZ@Z(ptr ptr) SpinWait_ctor
#@ varargs -arch=win32 ??0SchedulerPolicy@Concurrency@@QAA@IZZ(ptr long) SchedulerPolicy_ctor_policies
#@ varargs -arch=win64 ??0SchedulerPolicy@Concurrency@@QEAA@_KZZ(ptr long) SchedulerPolicy_ctor_policies
#@ thiscall -arch=i386 ??0SchedulerPolicy@Concurrency@@QAE@ABV01@@Z(ptr ptr) SchedulerPolicy_copy_ctor
#@ cdecl -arch=win64 ??0SchedulerPolicy@Concurrency@@QEAA@AEBV01@@Z(ptr ptr) SchedulerPolicy_copy_ctor
#@ thiscall -arch=i386 ??0SchedulerPolicy@Concurrency@@QAE@XZ(ptr) SchedulerPolicy_ctor
#@ cdecl -arch=win64 ??0SchedulerPolicy@Concurrency@@QEAA@XZ(ptr) SchedulerPolicy_ctor
#@ thiscall -arch=win32 ??0_NonReentrantBlockingLock@details@Concurrency@@QAE@XZ(ptr) _ReentrantBlockingLock_ctor
#@ cdecl -arch=win64 ??0_NonReentrantBlockingLock@details@Concurrency@@QEAA@XZ(ptr) _ReentrantBlockingLock_ctor
@ stub -arch=win32 ??0_NonReentrantPPLLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0_NonReentrantPPLLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0_ReaderWriterLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0_ReaderWriterLock@details@Concurrency@@QEAA@XZ
#@ thiscall -arch=win32 ??0_ReentrantBlockingLock@details@Concurrency@@QAE@XZ(ptr) _ReentrantBlockingLock_ctor
#@ cdecl -arch=win64 ??0_ReentrantBlockingLock@details@Concurrency@@QEAA@XZ(ptr) _ReentrantBlockingLock_ctor
@ stub -arch=win32 ??0_ReentrantLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0_ReentrantLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0_ReentrantPPLLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0_ReentrantPPLLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0_Scoped_lock@_NonReentrantPPLLock@details@Concurrency@@QAE@AAV123@@Z
@ stub -arch=win64 ??0_Scoped_lock@_NonReentrantPPLLock@details@Concurrency@@QEAA@AEAV123@@Z
@ stub -arch=win32 ??0_Scoped_lock@_ReentrantPPLLock@details@Concurrency@@QAE@AAV123@@Z
@ stub -arch=win64 ??0_Scoped_lock@_ReentrantPPLLock@details@Concurrency@@QEAA@AEAV123@@Z
@ stub -arch=win32 ??0_SpinLock@details@Concurrency@@QAE@ACJ@Z
@ stub -arch=win64 ??0_SpinLock@details@Concurrency@@QEAA@AECJ@Z
@ stub -arch=win32 ??0_TaskCollection@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0_TaskCollection@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0_Timer@details@Concurrency@@IAE@I_N@Z
@ stub -arch=win64 ??0_Timer@details@Concurrency@@IEAA@I_N@Z
#@ thiscall -arch=i386 ??0__non_rtti_object@std@@QAE@ABV01@@Z(ptr ptr) MSVCRT___non_rtti_object_copy_ctor
#@ cdecl -arch=win64 ??0__non_rtti_object@std@@QEAA@AEBV01@@Z(ptr ptr) MSVCRT___non_rtti_object_copy_ctor
#@ thiscall -arch=i386 ??0__non_rtti_object@std@@QAE@PBD@Z(ptr ptr) MSVCRT___non_rtti_object_ctor
#@ cdecl -arch=win64 ??0__non_rtti_object@std@@QEAA@PEBD@Z(ptr ptr) MSVCRT___non_rtti_object_ctor
@ thiscall -arch=i386 ??0bad_cast@std@@AAE@PBQBD@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_ctor
@ cdecl -arch=win64 ??0bad_cast@std@@AEAA@PEBQEBD@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_ctor
@ thiscall -arch=i386 ??0bad_cast@std@@QAE@ABV01@@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_copy_ctor
@ cdecl -arch=win64 ??0bad_cast@std@@QEAA@AEBV01@@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_copy_ctor
@ thiscall -arch=i386 ??0bad_cast@std@@QAE@PBD@Z(ptr str) __thiscall_MSVCRT_bad_cast_ctor_charptr
@ cdecl -arch=win64 ??0bad_cast@std@@QEAA@PEBD@Z(ptr str) __thiscall_MSVCRT_bad_cast_ctor_charptr
@ stub -arch=win32 ??0bad_target@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0bad_target@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0bad_target@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0bad_target@Concurrency@@QEAA@XZ
#@ thiscall -arch=i386 ??0bad_typeid@std@@QAE@ABV01@@Z(ptr ptr) MSVCRT_bad_typeid_copy_ctor
#@ cdecl -arch=win64 ??0bad_typeid@std@@QEAA@AEBV01@@Z(ptr ptr) MSVCRT_bad_typeid_copy_ctor
#@ thiscall -arch=i386 ??0bad_typeid@std@@QAE@PBD@Z(ptr str) MSVCRT_bad_typeid_ctor
#@ cdecl -arch=win64 ??0bad_typeid@std@@QEAA@PEBD@Z(ptr str) MSVCRT_bad_typeid_ctor
@ stub -arch=win32 ??0context_self_unblock@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0context_self_unblock@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0context_self_unblock@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0context_self_unblock@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0context_unblock_unbalanced@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0context_unblock_unbalanced@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0context_unblock_unbalanced@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0context_unblock_unbalanced@Concurrency@@QEAA@XZ
#@ thiscall -arch=win32 ??0critical_section@Concurrency@@QAE@XZ(ptr) critical_section_ctor
#@ cdecl -arch=win64 ??0critical_section@Concurrency@@QEAA@XZ(ptr) critical_section_ctor
@ stub -arch=win32 ??0default_scheduler_exists@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0default_scheduler_exists@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0default_scheduler_exists@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0default_scheduler_exists@Concurrency@@QEAA@XZ
#@ thiscall -arch=win32 ??0event@Concurrency@@QAE@XZ(ptr) event_ctor
#@ cdecl -arch=win64 ??0event@Concurrency@@QEAA@XZ(ptr) event_ctor
@ thiscall -arch=i386 ??0exception@std@@QAE@ABQBD@Z(ptr ptr) __thiscall_MSVCRT_exception_ctor
@ cdecl -arch=win64 ??0exception@std@@QEAA@AEBQEBD@Z(ptr ptr) __thiscall_MSVCRT_exception_ctor
@ thiscall -arch=i386 ??0exception@std@@QAE@ABQBDH@Z(ptr ptr long) __thiscall_MSVCRT_exception_ctor_noalloc
@ cdecl -arch=win64 ??0exception@std@@QEAA@AEBQEBDH@Z(ptr ptr long) __thiscall_MSVCRT_exception_ctor_noalloc
@ thiscall -arch=i386 ??0exception@std@@QAE@ABV01@@Z(ptr ptr) __thiscall_MSVCRT_exception_copy_ctor
@ cdecl -arch=win64 ??0exception@std@@QEAA@AEBV01@@Z(ptr ptr) __thiscall_MSVCRT_exception_copy_ctor
@ thiscall -arch=i386 ??0exception@std@@QAE@XZ(ptr) __thiscall_MSVCRT_exception_default_ctor
@ cdecl -arch=win64 ??0exception@std@@QEAA@XZ(ptr) __thiscall_MSVCRT_exception_default_ctor
#@ thiscall -arch=i386 ??0improper_lock@Concurrency@@QAE@PBD@Z(ptr str) improper_lock_ctor_str
#@ cdecl -arch=win64 ??0improper_lock@Concurrency@@QEAA@PEBD@Z(ptr str) improper_lock_ctor_str
#@ thiscall -arch=i386 ??0improper_lock@Concurrency@@QAE@XZ(ptr) improper_lock_ctor
#@ cdecl -arch=win64 ??0improper_lock@Concurrency@@QEAA@XZ(ptr) improper_lock_ctor
#@ thiscall -arch=i386 ??0improper_scheduler_attach@Concurrency@@QAE@PBD@Z(ptr str) improper_scheduler_attach_ctor_str
#@ cdecl -arch=win64 ??0improper_scheduler_attach@Concurrency@@QEAA@PEBD@Z(ptr str) improper_scheduler_attach_ctor_str
#@ thiscall -arch=i386 ??0improper_scheduler_attach@Concurrency@@QAE@XZ(ptr) improper_scheduler_attach_ctor
#@ cdecl -arch=win64 ??0improper_scheduler_attach@Concurrency@@QEAA@XZ(ptr) improper_scheduler_attach_ctor
#@ thiscall -arch=i386 ??0improper_scheduler_detach@Concurrency@@QAE@PBD@Z(ptr str) improper_scheduler_detach_ctor_str
#@ cdecl -arch=win64 ??0improper_scheduler_detach@Concurrency@@QEAA@PEBD@Z(ptr str) improper_scheduler_detach_ctor_str
#@ thiscall -arch=i386 ??0improper_scheduler_detach@Concurrency@@QAE@XZ(ptr) improper_scheduler_detach_ctor
#@ cdecl -arch=win64 ??0improper_scheduler_detach@Concurrency@@QEAA@XZ(ptr) improper_scheduler_detach_ctor
@ stub -arch=win32 ??0improper_scheduler_reference@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0improper_scheduler_reference@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0improper_scheduler_reference@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0improper_scheduler_reference@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0invalid_link_target@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0invalid_link_target@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0invalid_link_target@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0invalid_link_target@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0invalid_multiple_scheduling@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0invalid_multiple_scheduling@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0invalid_multiple_scheduling@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0invalid_multiple_scheduling@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0invalid_operation@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0invalid_operation@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0invalid_operation@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0invalid_operation@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0invalid_oversubscribe_operation@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0invalid_oversubscribe_operation@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0invalid_oversubscribe_operation@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0invalid_oversubscribe_operation@Concurrency@@QEAA@XZ
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_key@Concurrency@@QAE@PBD@Z(ptr str) invalid_scheduler_policy_key_ctor_str
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_key@Concurrency@@QEAA@PEBD@Z(ptr str) invalid_scheduler_policy_key_ctor_str
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_key@Concurrency@@QAE@XZ(ptr) invalid_scheduler_policy_key_ctor
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_key@Concurrency@@QEAA@XZ(ptr) invalid_scheduler_policy_key_ctor
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_thread_specification@Concurrency@@QAE@PBD@Z(ptr str) invalid_scheduler_policy_thread_specification_ctor_str
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_thread_specification@Concurrency@@QEAA@PEBD@Z(ptr str) invalid_scheduler_policy_thread_specification_ctor_str
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_thread_specification@Concurrency@@QAE@XZ(ptr) invalid_scheduler_policy_thread_specification_ctor
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_thread_specification@Concurrency@@QEAA@XZ(ptr) invalid_scheduler_policy_thread_specification_ctor
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_value@Concurrency@@QAE@PBD@Z(ptr str) invalid_scheduler_policy_value_ctor_str
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_value@Concurrency@@QEAA@PEBD@Z(ptr str) invalid_scheduler_policy_value_ctor_str
#@ thiscall -arch=i386 ??0invalid_scheduler_policy_value@Concurrency@@QAE@XZ(ptr) invalid_scheduler_policy_value_ctor
#@ cdecl -arch=win64 ??0invalid_scheduler_policy_value@Concurrency@@QEAA@XZ(ptr) invalid_scheduler_policy_value_ctor
@ stub -arch=win32 ??0message_not_found@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0message_not_found@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0message_not_found@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0message_not_found@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0missing_wait@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0missing_wait@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0missing_wait@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0missing_wait@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0nested_scheduler_missing_detach@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0nested_scheduler_missing_detach@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0nested_scheduler_missing_detach@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0nested_scheduler_missing_detach@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0operation_timed_out@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0operation_timed_out@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0operation_timed_out@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0operation_timed_out@Concurrency@@QEAA@XZ
#@ thiscall -arch=win32 ??0reader_writer_lock@Concurrency@@QAE@XZ(ptr) reader_writer_lock_ctor
#@ cdecl -arch=win64 ??0reader_writer_lock@Concurrency@@QEAA@XZ(ptr) reader_writer_lock_ctor
@ stub -arch=win32 ??0scheduler_not_attached@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0scheduler_not_attached@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0scheduler_not_attached@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0scheduler_not_attached@Concurrency@@QEAA@XZ
#@ thiscall -arch=i386 ??0scheduler_resource_allocation_error@Concurrency@@QAE@J@Z(ptr long) scheduler_resource_allocation_error_ctor
#@ cdecl -arch=win64 ??0scheduler_resource_allocation_error@Concurrency@@QEAA@J@Z(ptr long) scheduler_resource_allocation_error_ctor
#@ thiscall -arch=i386 ??0scheduler_resource_allocation_error@Concurrency@@QAE@PBDJ@Z(ptr str long) scheduler_resource_allocation_error_ctor_name
#@ cdecl -arch=win64 ??0scheduler_resource_allocation_error@Concurrency@@QEAA@PEBDJ@Z(ptr str long) scheduler_resource_allocation_error_ctor_name
#@ thiscall -arch=win32 ??0scoped_lock@critical_section@Concurrency@@QAE@AAV12@@Z(ptr ptr) critical_section_scoped_lock_ctor
#@ cdecl -arch=win64 ??0scoped_lock@critical_section@Concurrency@@QEAA@AEAV12@@Z(ptr ptr) critical_section_scoped_lock_ctor
#@ thiscall -arch=win32 ??0scoped_lock@reader_writer_lock@Concurrency@@QAE@AAV12@@Z(ptr ptr) reader_writer_lock_scoped_lock_ctor
#@ cdecl -arch=win64 ??0scoped_lock@reader_writer_lock@Concurrency@@QEAA@AEAV12@@Z(ptr ptr) reader_writer_lock_scoped_lock_ctor
#@ thiscall -arch=win32 ??0scoped_lock_read@reader_writer_lock@Concurrency@@QAE@AAV12@@Z(ptr ptr) reader_writer_lock_scoped_lock_read_ctor
#@ cdecl -arch=win64 ??0scoped_lock_read@reader_writer_lock@Concurrency@@QEAA@AEAV12@@Z(ptr ptr) reader_writer_lock_scoped_lock_read_ctor
@ stub -arch=win32 ??0task_canceled@details@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0task_canceled@details@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0task_canceled@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0task_canceled@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??0unsupported_os@Concurrency@@QAE@PBD@Z
@ stub -arch=win64 ??0unsupported_os@Concurrency@@QEAA@PEBD@Z
@ stub -arch=win32 ??0unsupported_os@Concurrency@@QAE@XZ
@ stub -arch=win64 ??0unsupported_os@Concurrency@@QEAA@XZ
#@ thiscall -arch=i386 ??1SchedulerPolicy@Concurrency@@QAE@XZ(ptr) SchedulerPolicy_dtor
#@ cdecl -arch=win64 ??1SchedulerPolicy@Concurrency@@QEAA@XZ(ptr) SchedulerPolicy_dtor
#@ thiscall -arch=win32 ??1_NonReentrantBlockingLock@details@Concurrency@@QAE@XZ(ptr) _ReentrantBlockingLock_dtor
#@ cdecl -arch=win64 ??1_NonReentrantBlockingLock@details@Concurrency@@QEAA@XZ(ptr) _ReentrantBlockingLock_dtor
#@ thiscall -arch=win32 ??1_ReentrantBlockingLock@details@Concurrency@@QAE@XZ(ptr) _ReentrantBlockingLock_dtor
#@ cdecl -arch=win64 ??1_ReentrantBlockingLock@details@Concurrency@@QEAA@XZ(ptr) _ReentrantBlockingLock_dtor
@ stub -arch=win32 ??1_Scoped_lock@_NonReentrantPPLLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??1_Scoped_lock@_NonReentrantPPLLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??1_Scoped_lock@_ReentrantPPLLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??1_Scoped_lock@_ReentrantPPLLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??1_SpinLock@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??1_SpinLock@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??1_TaskCollection@details@Concurrency@@QAE@XZ
@ stub -arch=win64 ??1_TaskCollection@details@Concurrency@@QEAA@XZ
@ stub -arch=win32 ??1_Timer@details@Concurrency@@IAE@XZ
@ stub -arch=win64 ??1_Timer@details@Concurrency@@IEAA@XZ
#@ thiscall -arch=i386 ??1__non_rtti_object@std@@UAE@XZ(ptr) MSVCRT___non_rtti_object_dtor
#@ cdecl -arch=win64 ??1__non_rtti_object@std@@UEAA@XZ(ptr) MSVCRT___non_rtti_object_dtor
@ thiscall -arch=i386 ??1bad_cast@std@@UAE@XZ(ptr) __thiscall_MSVCRT_bad_cast_dtor
@ cdecl -arch=win64 ??1bad_cast@std@@UEAA@XZ(ptr) __thiscall_MSVCRT_bad_cast_dtor
#@ thiscall -arch=i386 ??1bad_typeid@std@@UAE@XZ(ptr) MSVCRT_bad_typeid_dtor
#@ cdecl -arch=win64 ??1bad_typeid@std@@UEAA@XZ(ptr) MSVCRT_bad_typeid_dtor
#@ thiscall -arch=win32 ??1critical_section@Concurrency@@QAE@XZ(ptr) critical_section_dtor
#@ cdecl -arch=win64 ??1critical_section@Concurrency@@QEAA@XZ(ptr) critical_section_dtor
#@ thiscall -arch=win32 ??1event@Concurrency@@QAE@XZ(ptr) event_dtor
#@ cdecl -arch=win64 ??1event@Concurrency@@QEAA@XZ(ptr) event_dtor
@ thiscall -arch=i386 ??1exception@std@@UAE@XZ(ptr) __thiscall_MSVCRT_exception_dtor
@ cdecl -arch=win64 ??1exception@std@@UEAA@XZ(ptr) __thiscall_MSVCRT_exception_dtor
#@ thiscall -arch=win32 ??1reader_writer_lock@Concurrency@@QAE@XZ(ptr) reader_writer_lock_dtor
#@ cdecl -arch=win64 ??1reader_writer_lock@Concurrency@@QEAA@XZ(ptr) reader_writer_lock_dtor
#@ thiscall -arch=win32 ??1scoped_lock@critical_section@Concurrency@@QAE@XZ(ptr) critical_section_scoped_lock_dtor
#@ cdecl -arch=win64 ??1scoped_lock@critical_section@Concurrency@@QEAA@XZ(ptr) critical_section_scoped_lock_dtor
#@ thiscall -arch=win32 ??1scoped_lock@reader_writer_lock@Concurrency@@QAE@XZ(ptr) reader_writer_lock_scoped_lock_dtor
#@ cdecl -arch=win64 ??1scoped_lock@reader_writer_lock@Concurrency@@QEAA@XZ(ptr) reader_writer_lock_scoped_lock_dtor
#@ thiscall -arch=win32 ??1scoped_lock_read@reader_writer_lock@Concurrency@@QAE@XZ(ptr) reader_writer_lock_scoped_lock_read_dtor
#@ cdecl -arch=win64 ??1scoped_lock_read@reader_writer_lock@Concurrency@@QEAA@XZ(ptr) reader_writer_lock_scoped_lock_read_dtor
@ cdecl -arch=arm ??1type_info@@UAA@XZ(ptr) MSVCRT_type_info_dtor
@ thiscall -arch=i386 ??1type_info@@UAE@XZ(ptr) __thiscall_MSVCRT_type_info_dtor
@ cdecl -arch=win64 ??1type_info@@UEAA@XZ(ptr) __thiscall_MSVCRT_type_info_dtor
@ cdecl -arch=win32 ??2@YAPAXI@Z(long) MSVCRT_operator_new
@ cdecl -arch=win64 ??2@YAPEAX_K@Z(long) MSVCRT_operator_new
@ cdecl -arch=win32 ??2@YAPAXIHPBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win64 ??2@YAPEAX_KHPEBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win32 ??3@YAXPAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win64 ??3@YAXPEAX@Z(ptr) MSVCRT_operator_delete
@ stub -arch=win32 ??4?$_SpinWait@$00@details@Concurrency@@QAEAAV012@ABV012@@Z
@ stub -arch=win64 ??4?$_SpinWait@$00@details@Concurrency@@QEAAAEAV012@AEBV012@@Z
@ stub -arch=win32 ??4?$_SpinWait@$0A@@details@Concurrency@@QAEAAV012@ABV012@@Z
@ stub -arch=win64 ??4?$_SpinWait@$0A@@details@Concurrency@@QEAAAEAV012@AEBV012@@Z
#@ thiscall -arch=i386 ??4SchedulerPolicy@Concurrency@@QAEAAV01@ABV01@@Z(ptr ptr) SchedulerPolicy_op_assign
#@ cdecl -arch=win64 ??4SchedulerPolicy@Concurrency@@QEAAAEAV01@AEBV01@@Z(ptr ptr) SchedulerPolicy_op_assign
#@ thiscall -arch=i386 ??4__non_rtti_object@std@@QAEAAV01@ABV01@@Z(ptr ptr) MSVCRT___non_rtti_object_opequals
#@ cdecl -arch=win64 ??4__non_rtti_object@std@@QEAAAEAV01@AEBV01@@Z(ptr ptr) MSVCRT___non_rtti_object_opequals
@ thiscall -arch=i386 ??4bad_cast@std@@QAEAAV01@ABV01@@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_opequals
@ cdecl -arch=win64 ??4bad_cast@std@@QEAAAEAV01@AEBV01@@Z(ptr ptr) __thiscall_MSVCRT_bad_cast_opequals
#@ thiscall -arch=i386 ??4bad_typeid@std@@QAEAAV01@ABV01@@Z(ptr ptr) MSVCRT_bad_typeid_opequals
#@ cdecl -arch=win64 ??4bad_typeid@std@@QEAAAEAV01@AEBV01@@Z(ptr ptr) MSVCRT_bad_typeid_opequals
@ thiscall -arch=i386 ??4exception@std@@QAEAAV01@ABV01@@Z(ptr ptr) __thiscall_MSVCRT_exception_opequals
@ cdecl -arch=win64 ??4exception@std@@QEAAAEAV01@AEBV01@@Z(ptr ptr) __thiscall_MSVCRT_exception_opequals
@ cdecl -arch=arm ??8type_info@@QBA_NABV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opequals_equals
@ thiscall -arch=i386 ??8type_info@@QBE_NABV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opequals_equals
@ cdecl -arch=win64 ??8type_info@@QEBA_NAEBV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opequals_equals
@ cdecl -arch=arm ??9type_info@@QBA_NABV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opnot_equals
@ thiscall -arch=i386 ??9type_info@@QBE_NABV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opnot_equals
@ cdecl -arch=win64 ??9type_info@@QEBA_NAEBV0@@Z(ptr ptr) __thiscall_MSVCRT_type_info_opnot_equals
#@ extern ??_7__non_rtti_object@std@@6B@ MSVCRT___non_rtti_object_vtable
@ extern ??_7bad_cast@std@@6B@ MSVCRT_bad_cast_vtable
#@ extern ??_7bad_typeid@std@@6B@ MSVCRT_bad_typeid_vtable
@ extern ??_7exception@@6B@ MSVCRT_exception_old_vtable
@ extern ??_7exception@std@@6B@ MSVCRT_exception_vtable
#@ thiscall -arch=win32 ??_F?$_SpinWait@$00@details@Concurrency@@QAEXXZ(ptr) SpinWait_dtor
#@ cdecl -arch=win64 ??_F?$_SpinWait@$00@details@Concurrency@@QEAAXXZ(ptr) SpinWait_dtor
#@ thiscall -arch=win32 ??_F?$_SpinWait@$0A@@details@Concurrency@@QAEXXZ(ptr) SpinWait_dtor
#@ cdecl -arch=win64 ??_F?$_SpinWait@$0A@@details@Concurrency@@QEAAXXZ(ptr) SpinWait_dtor
@ thiscall -arch=i386 ??_Fbad_cast@std@@QAEXXZ(ptr) __thiscall_MSVCRT_bad_cast_default_ctor
@ cdecl -arch=win64 ??_Fbad_cast@std@@QEAAXXZ(ptr) __thiscall_MSVCRT_bad_cast_default_ctor
#@ thiscall -arch=i386 ??_Fbad_typeid@std@@QAEXXZ(ptr) MSVCRT_bad_typeid_default_ctor
#@ cdecl -arch=win64 ??_Fbad_typeid@std@@QEAAXXZ(ptr) MSVCRT_bad_typeid_default_ctor
@ cdecl -arch=win32 ??_U@YAPAXI@Z(long) MSVCRT_operator_new
@ cdecl -arch=win64 ??_U@YAPEAX_K@Z(long) MSVCRT_operator_new
@ cdecl -arch=win32 ??_U@YAPAXIHPBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win64 ??_U@YAPEAX_KHPEBDH@Z(long long str long) MSVCRT_operator_new_dbg
@ cdecl -arch=win32 ??_V@YAXPAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win64 ??_V@YAXPEAX@Z(ptr) MSVCRT_operator_delete
@ cdecl -arch=win32 ?Alloc@Concurrency@@YAPAXI@Z(long) Concurrency_Alloc
@ cdecl -arch=win64 ?Alloc@Concurrency@@YAPEAX_K@Z(long) Concurrency_Alloc
@ cdecl ?Block@Context@Concurrency@@SAXXZ() Context_Block
@ cdecl -arch=win32 ?Create@CurrentScheduler@Concurrency@@SAXABVSchedulerPolicy@2@@Z(ptr) CurrentScheduler_Create
@ cdecl -arch=win64 ?Create@CurrentScheduler@Concurrency@@SAXAEBVSchedulerPolicy@2@@Z(ptr) CurrentScheduler_Create
@ cdecl -arch=win32 ?Create@Scheduler@Concurrency@@SAPAV12@ABVSchedulerPolicy@2@@Z(ptr) Scheduler_Create
@ cdecl -arch=win64 ?Create@Scheduler@Concurrency@@SAPEAV12@AEBVSchedulerPolicy@2@@Z(ptr) Scheduler_Create
@ stub -arch=win32 ?CreateResourceManager@Concurrency@@YAPAUIResourceManager@1@XZ
@ stub -arch=win64 ?CreateResourceManager@Concurrency@@YAPEAUIResourceManager@1@XZ
@ cdecl -arch=win32 ?CreateScheduleGroup@CurrentScheduler@Concurrency@@SAPAVScheduleGroup@2@XZ() CurrentScheduler_CreateScheduleGroup
@ cdecl -arch=win64 ?CreateScheduleGroup@CurrentScheduler@Concurrency@@SAPEAVScheduleGroup@2@XZ() CurrentScheduler_CreateScheduleGroup
@ cdecl -arch=win32 ?CurrentContext@Context@Concurrency@@SAPAV12@XZ() Context_CurrentContext
@ cdecl -arch=win64 ?CurrentContext@Context@Concurrency@@SAPEAV12@XZ() Context_CurrentContext
@ cdecl ?Detach@CurrentScheduler@Concurrency@@SAXXZ() CurrentScheduler_Detach
@ stub ?DisableTracing@Concurrency@@YAJXZ
@ stub ?EnableTracing@Concurrency@@YAJXZ
@ cdecl -arch=win32 ?Free@Concurrency@@YAXPAX@Z(ptr) Concurrency_Free
@ cdecl -arch=win64 ?Free@Concurrency@@YAXPEAX@Z(ptr) Concurrency_Free
@ cdecl -arch=win32 ?Get@CurrentScheduler@Concurrency@@SAPAVScheduler@2@XZ() CurrentScheduler_Get
@ cdecl -arch=win64 ?Get@CurrentScheduler@Concurrency@@SAPEAVScheduler@2@XZ() CurrentScheduler_Get
@ stub ?GetExecutionContextId@Concurrency@@YAIXZ
@ cdecl ?GetNumberOfVirtualProcessors@CurrentScheduler@Concurrency@@SAIXZ() CurrentScheduler_GetNumberOfVirtualProcessors
@ stub ?GetOSVersion@Concurrency@@YA?AW4OSVersion@IResourceManager@1@XZ
@ cdecl ?GetPolicy@CurrentScheduler@Concurrency@@SA?AVSchedulerPolicy@2@XZ(ptr) CurrentScheduler_GetPolicy
#@ thiscall -arch=i386 ?GetPolicyValue@SchedulerPolicy@Concurrency@@QBEIW4PolicyElementKey@2@@Z(ptr long) SchedulerPolicy_GetPolicyValue
#@ cdecl -arch=win64 ?GetPolicyValue@SchedulerPolicy@Concurrency@@QEBAIW4PolicyElementKey@2@@Z(ptr long) SchedulerPolicy_GetPolicyValue
@ stub ?GetProcessorCount@Concurrency@@YAIXZ
@ stub ?GetProcessorNodeCount@Concurrency@@YAIXZ
@ stub ?GetSchedulerId@Concurrency@@YAIXZ
@ stub -arch=win32 ?GetSharedTimerQueue@details@Concurrency@@YAPAXXZ
@ stub -arch=win64 ?GetSharedTimerQueue@details@Concurrency@@YAPEAXXZ
@ cdecl ?Id@Context@Concurrency@@SAIXZ() Context_Id
@ cdecl ?Id@CurrentScheduler@Concurrency@@SAIXZ() CurrentScheduler_Id
@ cdecl ?IsCurrentTaskCollectionCanceling@Context@Concurrency@@SA_NXZ() Context_IsCurrentTaskCollectionCanceling
@ stub -arch=win32 ?Log2@details@Concurrency@@YAKI@Z
@ stub -arch=win64 ?Log2@details@Concurrency@@YAK_K@Z
@ cdecl ?Oversubscribe@Context@Concurrency@@SAX_N@Z(long) Context_Oversubscribe
@ cdecl -arch=win32 ?RegisterShutdownEvent@CurrentScheduler@Concurrency@@SAXPAX@Z(long) CurrentScheduler_RegisterShutdownEvent
@ cdecl -arch=win64 ?RegisterShutdownEvent@CurrentScheduler@Concurrency@@SAXPEAX@Z(long) CurrentScheduler_RegisterShutdownEvent
@ cdecl ?ResetDefaultSchedulerPolicy@Scheduler@Concurrency@@SAXXZ() Scheduler_ResetDefaultSchedulerPolicy
@ cdecl ?ScheduleGroupId@Context@Concurrency@@SAIXZ() Context_ScheduleGroupId
#@ cdecl -arch=win32 ?ScheduleTask@CurrentScheduler@Concurrency@@SAXP6AXPAX@Z0@Z(ptr ptr) CurrentScheduler_ScheduleTask
#@ cdecl -arch=win64 ?ScheduleTask@CurrentScheduler@Concurrency@@SAXP6AXPEAX@Z0@Z(ptr ptr) CurrentScheduler_ScheduleTask
#@ thiscall -arch=i386 ?SetConcurrencyLimits@SchedulerPolicy@Concurrency@@QAEXII@Z(ptr long long) SchedulerPolicy_SetConcurrencyLimits
#@ cdecl -arch=win64 ?SetConcurrencyLimits@SchedulerPolicy@Concurrency@@QEAAXII@Z(ptr long long) SchedulerPolicy_SetConcurrencyLimits
#@ cdecl -arch=win32 ?SetDefaultSchedulerPolicy@Scheduler@Concurrency@@SAXABVSchedulerPolicy@2@@Z(ptr) Scheduler_SetDefaultSchedulerPolicy
#@ cdecl -arch=win64 ?SetDefaultSchedulerPolicy@Scheduler@Concurrency@@SAXAEBVSchedulerPolicy@2@@Z(ptr) Scheduler_SetDefaultSchedulerPolicy
#@ thiscall -arch=i386 ?SetPolicyValue@SchedulerPolicy@Concurrency@@QAEIW4PolicyElementKey@2@I@Z(ptr long long) SchedulerPolicy_SetPolicyValue
#@ cdecl -arch=win64 ?SetPolicyValue@SchedulerPolicy@Concurrency@@QEAAIW4PolicyElementKey@2@I@Z(ptr long long) SchedulerPolicy_SetPolicyValue
@ cdecl ?VirtualProcessorId@Context@Concurrency@@SAIXZ() Context_VirtualProcessorId
@ cdecl ?Yield@Context@Concurrency@@SAXXZ() Context_Yield
@ stub -arch=win32 ?_Abort@_StructuredTaskCollection@details@Concurrency@@AAEXXZ
@ stub -arch=win64 ?_Abort@_StructuredTaskCollection@details@Concurrency@@AEAAXXZ
#@ thiscall -arch=win32 ?_Acquire@_NonReentrantBlockingLock@details@Concurrency@@QAEXXZ(ptr) _ReentrantBlockingLock__Acquire
#@ cdecl -arch=win64 ?_Acquire@_NonReentrantBlockingLock@details@Concurrency@@QEAAXXZ(ptr) _ReentrantBlockingLock__Acquire
@ stub -arch=win32 ?_Acquire@_NonReentrantPPLLock@details@Concurrency@@QAEXPAX@Z
@ stub -arch=win64 ?_Acquire@_NonReentrantPPLLock@details@Concurrency@@QEAAXPEAX@Z
#@ thiscall -arch=win32 ?_Acquire@_ReentrantBlockingLock@details@Concurrency@@QAEXXZ(ptr) _ReentrantBlockingLock__Acquire
#@ cdecl -arch=win64 ?_Acquire@_ReentrantBlockingLock@details@Concurrency@@QEAAXXZ(ptr) _ReentrantBlockingLock__Acquire
@ stub -arch=win32 ?_Acquire@_ReentrantLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Acquire@_ReentrantLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_Acquire@_ReentrantPPLLock@details@Concurrency@@QAEXPAX@Z
@ stub -arch=win64 ?_Acquire@_ReentrantPPLLock@details@Concurrency@@QEAAXPEAX@Z
@ stub -arch=win32 ?_AcquireRead@_ReaderWriterLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_AcquireRead@_ReaderWriterLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_AcquireWrite@_ReaderWriterLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_AcquireWrite@_ReaderWriterLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_Cancel@_StructuredTaskCollection@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Cancel@_StructuredTaskCollection@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_Cancel@_TaskCollection@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Cancel@_TaskCollection@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_CheckTaskCollection@_UnrealizedChore@details@Concurrency@@IAEXXZ
@ stub -arch=win64 ?_CheckTaskCollection@_UnrealizedChore@details@Concurrency@@IEAAXXZ
@ stub -arch=win32 ?_ConcRT_Assert@details@Concurrency@@YAXPBD0H@Z
@ stub -arch=win64 ?_ConcRT_Assert@details@Concurrency@@YAXPEBD0H@Z
@ stub -arch=win32 ?_ConcRT_CoreAssert@details@Concurrency@@YAXPBD0H@Z
@ stub -arch=win64 ?_ConcRT_CoreAssert@details@Concurrency@@YAXPEBD0H@Z
@ stub -arch=win32 ?_ConcRT_DumpMessage@details@Concurrency@@YAXPB_WZZ
@ stub -arch=win64 ?_ConcRT_DumpMessage@details@Concurrency@@YAXPEB_WZZ
@ stub -arch=win32 ?_ConcRT_Trace@details@Concurrency@@YAXHPB_WZZ
@ stub -arch=win64 ?_ConcRT_Trace@details@Concurrency@@YAXHPEB_WZZ
@ stub -arch=win32 ?_Copy_str@exception@std@@AAEXPBD@Z
@ stub -arch=win64 ?_Copy_str@exception@std@@AEAAXPEBD@Z
#@ thiscall -arch=win32 ?_DoYield@?$_SpinWait@$00@details@Concurrency@@IAEXXZ(ptr) SpinWait__DoYield
#@ cdecl -arch=win64 ?_DoYield@?$_SpinWait@$00@details@Concurrency@@IEAAXXZ(ptr) SpinWait__DoYield
#@ thiscall -arch=win32 ?_DoYield@?$_SpinWait@$0A@@details@Concurrency@@IAEXXZ(ptr) SpinWait__DoYield
#@ cdecl -arch=win64 ?_DoYield@?$_SpinWait@$0A@@details@Concurrency@@IEAAXXZ(ptr) SpinWait__DoYield
@ stub -arch=win32 ?_IsCanceling@_StructuredTaskCollection@details@Concurrency@@QAE_NXZ
@ stub -arch=win64 ?_IsCanceling@_StructuredTaskCollection@details@Concurrency@@QEAA_NXZ
@ stub -arch=win32 ?_IsCanceling@_TaskCollection@details@Concurrency@@QAE_NXZ
@ stub -arch=win64 ?_IsCanceling@_TaskCollection@details@Concurrency@@QEAA_NXZ
@ stub -arch=win32 ?_Name_base@type_info@@CAPBDPBV1@PAU__type_info_node@@@Z
@ stub -arch=win64 ?_Name_base@type_info@@CAPEBDPEBV1@PEAU__type_info_node@@@Z
@ stub -arch=win32 ?_Name_base_internal@type_info@@CAPBDPBV1@PAU__type_info_node@@@Z
@ stub -arch=win64 ?_Name_base_internal@type_info@@CAPEBDPEBV1@PEAU__type_info_node@@@Z
#@ thiscall -arch=win32 ?_NumberOfSpins@?$_SpinWait@$00@details@Concurrency@@IAEKXZ(ptr) SpinWait__NumberOfSpins
#@ cdecl -arch=win64 ?_NumberOfSpins@?$_SpinWait@$00@details@Concurrency@@IEAAKXZ(ptr) SpinWait__NumberOfSpins
#@ thiscall -arch=win32 ?_NumberOfSpins@?$_SpinWait@$0A@@details@Concurrency@@IAEKXZ(ptr) SpinWait__NumberOfSpins
#@ cdecl -arch=win64 ?_NumberOfSpins@?$_SpinWait@$0A@@details@Concurrency@@IEAAKXZ(ptr) SpinWait__NumberOfSpins
#@ thiscall -arch=win32 ?_Release@_NonReentrantBlockingLock@details@Concurrency@@QAEXXZ(ptr) _ReentrantBlockingLock__Release
#@ cdecl -arch=win64 ?_Release@_NonReentrantBlockingLock@details@Concurrency@@QEAAXXZ(ptr) _ReentrantBlockingLock__Release
@ stub -arch=win32 ?_Release@_NonReentrantPPLLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Release@_NonReentrantPPLLock@details@Concurrency@@QEAAXXZ
#@ thiscall -arch=win32 ?_Release@_ReentrantBlockingLock@details@Concurrency@@QAEXXZ(ptr) _ReentrantBlockingLock__Release
#@ cdecl -arch=win64 ?_Release@_ReentrantBlockingLock@details@Concurrency@@QEAAXXZ(ptr) _ReentrantBlockingLock__Release
@ stub -arch=win32 ?_Release@_ReentrantLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Release@_ReentrantLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_Release@_ReentrantPPLLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_Release@_ReentrantPPLLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_ReleaseRead@_ReaderWriterLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_ReleaseRead@_ReaderWriterLock@details@Concurrency@@QEAAXXZ
@ stub -arch=win32 ?_ReleaseWrite@_ReaderWriterLock@details@Concurrency@@QAEXXZ
@ stub -arch=win64 ?_ReleaseWrite@_ReaderWriterLock@details@Concurrency@@QEAAXXZ
#@ thiscall -arch=win32 ?_Reset@?$_SpinWait@$00@details@Concurrency@@IAEXXZ(ptr) SpinWait__Reset
#@ cdecl -arch=win64 ?_Reset@?$_SpinWait@$00@details@Concurrency@@IEAAXXZ(ptr) SpinWait__Reset
#@ thiscall -arch=win32 ?_Reset@?$_SpinWait@$0A@@details@Concurrency@@IAEXXZ(ptr) SpinWait__Reset
#@ cdecl -arch=win64 ?_Reset@?$_SpinWait@$0A@@details@Concurrency@@IEAAXXZ(ptr) SpinWait__Reset
@ stub -arch=win32 ?_RunAndWait@_StructuredTaskCollection@details@Concurrency@@QAG?AW4_TaskCollectionStatus@23@PAV_UnrealizedChore@23@@Z
@ stub -arch=win64 ?_RunAndWait@_StructuredTaskCollection@details@Concurrency@@QEAA?AW4_TaskCollectionStatus@23@PEAV_UnrealizedChore@23@@Z
@ stub -arch=win32 ?_RunAndWait@_TaskCollection@details@Concurrency@@QAG?AW4_TaskCollectionStatus@23@PAV_UnrealizedChore@23@@Z
@ stub -arch=win64 ?_RunAndWait@_TaskCollection@details@Concurrency@@QEAA?AW4_TaskCollectionStatus@23@PEAV_UnrealizedChore@23@@Z
@ stub -arch=win32 ?_Schedule@_StructuredTaskCollection@details@Concurrency@@QAEXPAV_UnrealizedChore@23@@Z
@ stub -arch=win64 ?_Schedule@_StructuredTaskCollection@details@Concurrency@@QEAAXPEAV_UnrealizedChore@23@@Z
@ stub -arch=win32 ?_Schedule@_TaskCollection@details@Concurrency@@QAEXPAV_UnrealizedChore@23@@Z
@ stub -arch=win64 ?_Schedule@_TaskCollection@details@Concurrency@@QEAAXPEAV_UnrealizedChore@23@@Z
#@ thiscall -arch=win32 ?_SetSpinCount@?$_SpinWait@$00@details@Concurrency@@QAEXI@Z(ptr long) SpinWait__SetSpinCount
#@ cdecl -arch=win64 ?_SetSpinCount@?$_SpinWait@$00@details@Concurrency@@QEAAXI@Z(ptr long) SpinWait__SetSpinCount
#@ thiscall -arch=win32 ?_SetSpinCount@?$_SpinWait@$0A@@details@Concurrency@@QAEXI@Z(ptr long) SpinWait__SetSpinCount
#@ cdecl -arch=win64 ?_SetSpinCount@?$_SpinWait@$0A@@details@Concurrency@@QEAAXI@Z(ptr long) SpinWait__SetSpinCount
#@ thiscall -arch=win32 ?_ShouldSpinAgain@?$_SpinWait@$00@details@Concurrency@@IAE_NXZ(ptr) SpinWait__ShouldSpinAgain
#@ cdecl -arch=win64 ?_ShouldSpinAgain@?$_SpinWait@$00@details@Concurrency@@IEAA_NXZ(ptr) SpinWait__ShouldSpinAgain
#@ thiscall -arch=win32 ?_ShouldSpinAgain@?$_SpinWait@$0A@@details@Concurrency@@IAE_NXZ(ptr) SpinWait__ShouldSpinAgain
#@ cdecl -arch=win64 ?_ShouldSpinAgain@?$_SpinWait@$0A@@details@Concurrency@@IEAA_NXZ(ptr) SpinWait__ShouldSpinAgain
#@ thiscall -arch=win32 ?_SpinOnce@?$_SpinWait@$00@details@Concurrency@@QAE_NXZ(ptr) SpinWait__SpinOnce
#@ cdecl -arch=win64 ?_SpinOnce@?$_SpinWait@$00@details@Concurrency@@QEAA_NXZ(ptr) SpinWait__SpinOnce
#@ thiscall -arch=win32 ?_SpinOnce@?$_SpinWait@$0A@@details@Concurrency@@QAE_NXZ(ptr) SpinWait__SpinOnce
#@ cdecl -arch=win64 ?_SpinOnce@?$_SpinWait@$0A@@details@Concurrency@@QEAA_NXZ(ptr) SpinWait__SpinOnce
@ cdecl ?_SpinYield@Context@Concurrency@@SAXXZ() Context__SpinYield
@ stub -arch=win32 ?_Start@_Timer@details@Concurrency@@IAEXXZ
@ stub -arch=win64 ?_Start@_Timer@details@Concurrency@@IEAAXXZ
@ stub -arch=win32 ?_Stop@_Timer@details@Concurrency@@IAEXXZ
@ stub -arch=win64 ?_Stop@_Timer@details@Concurrency@@IEAAXXZ
@ stub -arch=win32 ?_Tidy@exception@std@@AAEXXZ
@ stub -arch=win64 ?_Tidy@exception@std@@AEAAXXZ
#@ cdecl -arch=win32 ?_Trace_ppl_function@Concurrency@@YAXABU_GUID@@EW4ConcRT_EventType@1@@Z(ptr long long) Concurrency__Trace_ppl_function
#@ cdecl -arch=win64 ?_Trace_ppl_function@Concurrency@@YAXAEBU_GUID@@EW4ConcRT_EventType@1@@Z(ptr long long) Concurrency__Trace_ppl_function
#@ thiscall -arch=win32 ?_TryAcquire@_NonReentrantBlockingLock@details@Concurrency@@QAE_NXZ(ptr) _ReentrantBlockingLock__TryAcquire
#@ cdecl -arch=win64 ?_TryAcquire@_NonReentrantBlockingLock@details@Concurrency@@QEAA_NXZ(ptr) _ReentrantBlockingLock__TryAcquire
#@ thiscall -arch=win32 ?_TryAcquire@_ReentrantBlockingLock@details@Concurrency@@QAE_NXZ(ptr) _ReentrantBlockingLock__TryAcquire
#@ cdecl -arch=win64 ?_TryAcquire@_ReentrantBlockingLock@details@Concurrency@@QEAA_NXZ(ptr) _ReentrantBlockingLock__TryAcquire
@ stub -arch=win32 ?_TryAcquire@_ReentrantLock@details@Concurrency@@QAE_NXZ
@ stub -arch=win64 ?_TryAcquire@_ReentrantLock@details@Concurrency@@QEAA_NXZ
@ stub -arch=win32 ?_TryAcquireWrite@_ReaderWriterLock@details@Concurrency@@QAE_NXZ
@ stub -arch=win64 ?_TryAcquireWrite@_ReaderWriterLock@details@Concurrency@@QEAA_NXZ
@ stub -arch=win32 ?_Type_info_dtor@type_info@@CAXPAV1@@Z
@ stub -arch=win64 ?_Type_info_dtor@type_info@@CAXPEAV1@@Z
@ stub -arch=win32 ?_Type_info_dtor_internal@type_info@@CAXPAV1@@Z
@ stub -arch=win64 ?_Type_info_dtor_internal@type_info@@CAXPEAV1@@Z
@ stub -arch=win32 ?_UnderlyingYield@details@Concurrency@@YAXXZ
@ stub -arch=win64 ?_ValidateExecute@@YAHP6A_JXZ@Z
@ stub ?_ValidateExecute@@YAHP6GHXZ@Z
@ stub -arch=win32 ?_ValidateRead@@YAHPBXI@Z
@ stub -arch=win64 ?_ValidateRead@@YAHPEBXI@Z
@ stub -arch=win32 ?_ValidateWrite@@YAHPAXI@Z
@ stub -arch=win64 ?_ValidateWrite@@YAHPEAXI@Z
@ cdecl ?_Value@_SpinCount@details@Concurrency@@SAIXZ() SpinCount__Value
#@ cdecl -arch=win32 ?__ExceptionPtrAssign@@YAXPAXPBX@Z(ptr ptr) __ExceptionPtrAssign
#@ cdecl -arch=win64 ?__ExceptionPtrAssign@@YAXPEAXPEBX@Z(ptr ptr) __ExceptionPtrAssign
#@ cdecl -arch=win32 ?__ExceptionPtrCompare@@YA_NPBX0@Z(ptr ptr) __ExceptionPtrCompare
#@ cdecl -arch=win64 ?__ExceptionPtrCompare@@YA_NPEBX0@Z(ptr ptr) __ExceptionPtrCompare
#@ cdecl -arch=win32 ?__ExceptionPtrCopy@@YAXPAXPBX@Z(ptr ptr) __ExceptionPtrCopy
#@ cdecl -arch=win64 ?__ExceptionPtrCopy@@YAXPEAXPEBX@Z(ptr ptr) __ExceptionPtrCopy
#@ cdecl -arch=win32 ?__ExceptionPtrCopyException@@YAXPAXPBX1@Z(ptr ptr ptr) __ExceptionPtrCopyException
#@ cdecl -arch=win64 ?__ExceptionPtrCopyException@@YAXPEAXPEBX1@Z(ptr ptr ptr) __ExceptionPtrCopyException
#@ cdecl -arch=win32 ?__ExceptionPtrCreate@@YAXPAX@Z(ptr) __ExceptionPtrCreate
#@ cdecl -arch=win64 ?__ExceptionPtrCreate@@YAXPEAX@Z(ptr) __ExceptionPtrCreate
#@ cdecl -arch=win32 ?__ExceptionPtrCurrentException@@YAXPAX@Z(ptr) __ExceptionPtrCurrentException
#@ cdecl -arch=win64 ?__ExceptionPtrCurrentException@@YAXPEAX@Z(ptr) __ExceptionPtrCurrentException
#@ cdecl -arch=win32 ?__ExceptionPtrDestroy@@YAXPAX@Z(ptr) __ExceptionPtrDestroy
#@ cdecl -arch=win64 ?__ExceptionPtrDestroy@@YAXPEAX@Z(ptr) __ExceptionPtrDestroy
#@ cdecl -arch=win32 ?__ExceptionPtrRethrow@@YAXPBX@Z(ptr) __ExceptionPtrRethrow
#@ cdecl -arch=win64 ?__ExceptionPtrRethrow@@YAXPEBX@Z(ptr) __ExceptionPtrRethrow
@ cdecl __uncaught_exception() MSVCRT___uncaught_exception
@ stub ?_inconsistency@@YAXXZ
#@ cdecl -arch=win32 ?_invalid_parameter@@YAXPBG00II@Z(wstr wstr wstr long long) MSVCRT__invalid_parameter
#@ cdecl -arch=win64 ?_invalid_parameter@@YAXPEBG00I_K@Z(wstr wstr wstr long long) MSVCRT__invalid_parameter
#@ cdecl -arch=win32 ?_is_exception_typeof@@YAHABVtype_info@@PAU_EXCEPTION_POINTERS@@@Z(ptr ptr) _is_exception_typeof
#@ cdecl -arch=win64 ?_is_exception_typeof@@YAHAEBVtype_info@@PEAU_EXCEPTION_POINTERS@@@Z(ptr ptr) _is_exception_typeof
#@ cdecl -arch=arm ?_name_internal_method@type_info@@QBAPBDPAU__type_info_node@@@Z(ptr ptr) type_info_name_internal_method
#@ thiscall -arch=i386 ?_name_internal_method@type_info@@QBEPBDPAU__type_info_node@@@Z(ptr ptr) type_info_name_internal_method
#@ cdecl -arch=win64 ?_name_internal_method@type_info@@QEBAPEBDPEAU__type_info_node@@@Z(ptr ptr) type_info_name_internal_method
@ varargs -arch=win32 ?_open@@YAHPBDHH@Z(str long) MSVCRT__open
@ varargs -arch=win64 ?_open@@YAHPEBDHH@Z(str long) MSVCRT__open
@ cdecl -arch=win32 ?_query_new_handler@@YAP6AHI@ZXZ() MSVCRT__query_new_handler
@ cdecl -arch=win64 ?_query_new_handler@@YAP6AH_K@ZXZ() MSVCRT__query_new_handler
@ cdecl ?_query_new_mode@@YAHXZ() MSVCRT__query_new_mode
@ stub -arch=win32 ?_set_new_handler@@YAP6AHI@ZH@Z  # int (__cdecl*__cdecl _set_new_handler(int))(unsigned int)
@ stub -arch=win64 ?_set_new_handler@@YAP6AH_K@ZH@Z  # int (__cdecl*__cdecl _set_new_handler(int))(unsigned __int64)
@ cdecl -arch=win32 ?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z(ptr) MSVCRT__set_new_handler
@ cdecl -arch=win64 ?_set_new_handler@@YAP6AH_K@ZP6AH0@Z@Z(ptr) MSVCRT__set_new_handler
@ cdecl ?_set_new_mode@@YAHH@Z(long) MSVCRT__set_new_mode
@ stub -arch=win32 ?_set_se_translator@@YAP6AXIPAU_EXCEPTION_POINTERS@@@ZH@Z  # void (__cdecl*__cdecl _set_se_translator(int))(unsigned int,struct _EXCEPTION_POINTERS *)
@ stub -arch=win64 ?_set_se_translator@@YAP6AXIPEAU_EXCEPTION_POINTERS@@@ZH@Z  # void (__cdecl*__cdecl _set_se_translator(int))(unsigned int,struct _EXCEPTION_POINTERS * __ptr64)
#@ cdecl -arch=win32 ?_set_se_translator@@YAP6AXIPAU_EXCEPTION_POINTERS@@@ZP6AXI0@Z@Z(ptr) MSVCRT__set_se_translator
#@ cdecl -arch=win64 ?_set_se_translator@@YAP6AXIPEAU_EXCEPTION_POINTERS@@@ZP6AXI0@Z@Z(ptr) MSVCRT__set_se_translator
#@ cdecl -arch=win32 ?_sopen@@YAHPBDHHH@Z(str long long long) MSVCRT__sopen
#@ cdecl -arch=win64 ?_sopen@@YAHPEBDHHH@Z(str long long long) MSVCRT__sopen
@ cdecl -arch=win32 ?_type_info_dtor_internal_method@type_info@@QAEXXZ() MSVCRT_generic_stub  # public: void __thiscall type_info::_type_info_dtor_internal_method(void)
@ cdecl -arch=win64 ?_type_info_dtor_internal_method@type_info@@QEAAXXZ() MSVCRT_generic_stub  # public: void __cdecl type_info::_type_info_dtor_internal_method(void) __ptr64
#@ cdecl -arch=win32 ?_wopen@@YAHPB_WHH@Z(wstr long long) MSVCRT__wopen
#@ cdecl -arch=win64 ?_wopen@@YAHPEB_WHH@Z(wstr long long) MSVCRT__wopen
#@ cdecl -arch=win32 ?_wsopen@@YAHPB_WHHH@Z(wstr long long long) MSVCRT__wsopen
#@ cdecl -arch=win64 ?_wsopen@@YAHPEB_WHHH@Z(wstr long long long) MSVCRT__wsopen
@ thiscall -arch=i386 ?before@type_info@@QBEHABV1@@Z(ptr ptr) __thiscall_MSVCRT_type_info_before
@ cdecl -arch=win64 ?before@type_info@@QEBAHAEBV1@@Z(ptr ptr) __thiscall_MSVCRT_type_info_before
#@ thiscall -arch=i386 ?get_error_code@scheduler_resource_allocation_error@Concurrency@@QBEJXZ(ptr) scheduler_resource_allocation_error_get_error_code
#@ cdecl -arch=win64 ?get_error_code@scheduler_resource_allocation_error@Concurrency@@QEBAJXZ(ptr) scheduler_resource_allocation_error_get_error_code
#@ thiscall -arch=win32 ?lock@critical_section@Concurrency@@QAEXXZ(ptr) critical_section_lock
#@ cdecl -arch=win64 ?lock@critical_section@Concurrency@@QEAAXXZ(ptr) critical_section_lock
#@ thiscall -arch=win32 ?lock@reader_writer_lock@Concurrency@@QAEXXZ(ptr) reader_writer_lock_lock
#@ cdecl -arch=win64 ?lock@reader_writer_lock@Concurrency@@QEAAXXZ(ptr) reader_writer_lock_lock
#@ thiscall -arch=win32 ?lock_read@reader_writer_lock@Concurrency@@QAEXXZ(ptr) reader_writer_lock_lock_read
#@ cdecl -arch=win64 ?lock_read@reader_writer_lock@Concurrency@@QEAAXXZ(ptr) reader_writer_lock_lock_read
#@ thiscall -arch=win32 ?name@type_info@@QBEPBDPAU__type_info_node@@@Z(ptr ptr) type_info_name_internal_method
#@ cdecl -arch=win64 ?name@type_info@@QEBAPEBDPEAU__type_info_node@@@Z(ptr ptr) type_info_name_internal_method
#@ thiscall -arch=win32 ?native_handle@critical_section@Concurrency@@QAEAAV12@XZ(ptr) critical_section_native_handle
#@ cdecl -arch=win64 ?native_handle@critical_section@Concurrency@@QEAAAEAV12@XZ(ptr) critical_section_native_handle
#@ cdecl -arch=arm ?raw_name@type_info@@QBAPBDXZ(ptr) MSVCRT_type_info_raw_name
#@ thiscall -arch=i386 ?raw_name@type_info@@QBEPBDXZ(ptr) MSVCRT_type_info_raw_name
#@ cdecl -arch=win64 ?raw_name@type_info@@QEBAPEBDXZ(ptr) MSVCRT_type_info_raw_name
#@ thiscall -arch=win32 ?reset@event@Concurrency@@QAEXXZ(ptr) event_reset
#@ cdecl -arch=win64 ?reset@event@Concurrency@@QEAAXXZ(ptr) event_reset
#@ thiscall -arch=win32 ?set@event@Concurrency@@QAEXXZ(ptr) event_set
#@ cdecl -arch=win64 ?set@event@Concurrency@@QEAAXXZ(ptr) event_set
@ cdecl ?set_new_handler@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_new_handler
@ stub ?set_terminate@@YAP6AXXZH@Z
#@ cdecl ?set_terminate@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_terminate
@ stub ?set_unexpected@@YAP6AXXZH@Z
#@ cdecl ?set_unexpected@@YAP6AXXZP6AXXZ@Z(ptr) MSVCRT_set_unexpected
@ varargs ?swprintf@@YAHPAGIPBGZZ(ptr long wstr) MSVCRT__snwprintf
@ varargs ?swprintf@@YAHPA_WIPB_WZZ(ptr long wstr) MSVCRT__snwprintf
@ cdecl ?terminate@@YAXXZ() MSVCRT_terminate
#@ thiscall -arch=win32 ?try_lock@critical_section@Concurrency@@QAE_NXZ(ptr) critical_section_try_lock
#@ cdecl -arch=win64 ?try_lock@critical_section@Concurrency@@QEAA_NXZ(ptr) critical_section_try_lock
#@ thiscall -arch=win32 ?try_lock@reader_writer_lock@Concurrency@@QAE_NXZ(ptr) reader_writer_lock_try_lock
#@ cdecl -arch=win64 ?try_lock@reader_writer_lock@Concurrency@@QEAA_NXZ(ptr) reader_writer_lock_try_lock
#@ thiscall -arch=win32 ?try_lock_read@reader_writer_lock@Concurrency@@QAE_NXZ(ptr) reader_writer_lock_try_lock_read
#@ cdecl -arch=win64 ?try_lock_read@reader_writer_lock@Concurrency@@QEAA_NXZ(ptr) reader_writer_lock_try_lock_read
#@ cdecl ?unexpected@@YAXXZ() MSVCRT_unexpected
#@ thiscall -arch=win32 ?unlock@critical_section@Concurrency@@QAEXXZ(ptr) critical_section_unlock
#@ cdecl -arch=win64 ?unlock@critical_section@Concurrency@@QEAAXXZ(ptr) critical_section_unlock
#@ thiscall -arch=win32 ?unlock@reader_writer_lock@Concurrency@@QAEXXZ(ptr) reader_writer_lock_unlock
#@ cdecl -arch=win64 ?unlock@reader_writer_lock@Concurrency@@QEAAXXZ(ptr) reader_writer_lock_unlock
@ cdecl ?vswprintf@@YAHPA_WIPB_WPAD@Z(ptr long wstr ptr) MSVCRT__vsnwprintf
@ stub ?wait@Concurrency@@YAXI@Z
#@ thiscall -arch=win32 ?wait@event@Concurrency@@QAEII@Z(ptr) event_wait
#@ cdecl -arch=win64 ?wait@event@Concurrency@@QEAA_KI@Z(ptr) event_wait
#@ cdecl -arch=win32 ?wait_for_multiple@event@Concurrency@@SAIPAPAV12@I_NI@Z(ptr long long long) event_wait_for_multiple
#@ cdecl -arch=win64 ?wait_for_multiple@event@Concurrency@@SA_KPEAPEAV12@_K_NI@Z(ptr long long long) event_wait_for_multiple
@ thiscall -arch=i386 ?what@exception@std@@UBEPBDXZ(ptr) __thiscall_MSVCRT_what_exception
@ cdecl -arch=win64 ?what@exception@std@@UEBAPEBDXZ(ptr) __thiscall_MSVCRT_what_exception
@ cdecl -norelay $I10_OUTPUT(double long long long ptr) MSVCRT_I10_OUTPUT
@ cdecl -arch=i386 _CIacos()
@ cdecl -arch=i386 _CIasin()
@ cdecl -arch=i386 _CIatan()
@ cdecl -arch=i386 _CIatan2()
@ cdecl -arch=i386 _CIcos()
@ cdecl -arch=i386 _CIcosh()
@ cdecl -arch=i386 _CIexp()
@ cdecl -arch=i386 _CIfmod()
@ cdecl -arch=i386 _CIlog()
@ cdecl -arch=i386 _CIlog10()
@ cdecl -arch=i386 _CIpow()
@ cdecl -arch=i386 _CIsin()
@ cdecl -arch=i386 _CIsinh()
@ cdecl -arch=i386 _CIsqrt()
@ cdecl -arch=i386 _CItan()
@ cdecl -arch=i386 _CItanh()
#@ cdecl _CRT_RTC_INIT(ptr ptr long long long)
#@ cdecl _CRT_RTC_INITW(ptr ptr long long long)
@ cdecl _CreateFrameInfo(ptr ptr)
@ stdcall _CxxThrowException(ptr ptr) MSVCRT__CxxThrowException
#@ cdecl -arch=i386 -norelay _EH_prolog()
@ cdecl _FindAndUnlinkFrame(ptr)
@ cdecl _Getdays()
@ cdecl _Getmonths()
@ cdecl _Gettnames()
@ extern -arch=i386 _HUGE MSVCRT__HUGE
@ extern -arch=x86_64 _HUGE ucrtbase.__qemu_native_data__
@ cdecl _IsExceptionObjectToBeDestroyed(ptr)
@ stub _NLG_Dispatch2
@ stub _NLG_Return
@ stub _NLG_Return2
@ stub -arch=win64 _SetImageBase
@ stub -arch=win64 _SetThrowImageBase
@ cdecl _Strftime(ptr long str ptr ptr)
@ cdecl _XcptFilter(long ptr) MSVCRT__XcptFilter
#@ cdecl __AdjustPointer(ptr ptr)
@ stub __BuildCatchObject
@ stub __BuildCatchObjectHelper
@ stdcall -arch=x86_64 __C_specific_handler(ptr long ptr ptr) ntdll.__C_specific_handler
@ cdecl -arch=i386,x86_64,arm,arm64 __CppXcptFilter(long ptr)
@ stub __CxxCallUnwindDelDtor
@ stub __CxxCallUnwindDtor
@ stub __CxxCallUnwindStdDelDtor
@ stub __CxxCallUnwindVecDtor
#@ cdecl -arch=i386,x86_64,arm,arm64 __CxxDetectRethrow(ptr)
#@ cdecl -arch=i386,x86_64,arm,arm64 __CxxExceptionFilter(ptr ptr long ptr)
@ cdecl -arch=i386,x86_64,arm,arm64 -norelay __CxxFrameHandler(ptr ptr ptr ptr)
@ cdecl -arch=i386,x86_64,arm,arm64 -norelay __CxxFrameHandler2(ptr ptr ptr ptr) __CxxFrameHandler
@ cdecl -arch=i386,x86_64,arm,arm64 -norelay __CxxFrameHandler3(ptr ptr ptr ptr) __CxxFrameHandler
#@ stdcall -arch=i386 __CxxLongjmpUnwind(ptr)
#@ cdecl -arch=i386,x86_64,arm,arm64 __CxxQueryExceptionSize()
@ cdecl __CxxRegisterExceptionObject(ptr ptr)
@ cdecl __CxxUnregisterExceptionObject(ptr long)
@ cdecl __DestructExceptionObject(ptr)
@ stub __FrameUnwindFilter
#@ cdecl __RTCastToVoid(ptr) MSVCRT___RTCastToVoid
@ cdecl __RTDynamicCast(ptr long ptr ptr long) MSVCRT___RTDynamicCast
#@ cdecl __RTtypeid(ptr) MSVCRT___RTtypeid
@ cdecl __STRINGTOLD(ptr ptr str long)
@ stub __STRINGTOLD_L
@ stub __TypeMatch
@ cdecl ___lc_codepage_func()
@ cdecl ___lc_collate_cp_func()
@ cdecl ___lc_handle_func()
@ cdecl ___mb_cur_max_func() MSVCRT____mb_cur_max_func
@ cdecl ___mb_cur_max_l_func(ptr)
@ cdecl __acrt_iob_func(long) MSVCRT___acrt_iob_func
@ cdecl ___setlc_active_func() MSVCRT____setlc_active_func
@ cdecl ___unguarded_readlc_active_add_func() MSVCRT____unguarded_readlc_active_add_func
@ extern -arch=i386 __argc MSVCRT___argc
@ extern -arch=x86_64 __argc ucrtbase.__qemu_native_data__
@ extern -arch=i386 __argv MSVCRT___argv
@ extern -arch=x86_64 __argv ucrtbase.__qemu_native_data__
@ extern __badioinfo ucrtbase.__qemu_native_data__
@ cdecl __clean_type_info_names_internal(ptr)
@ cdecl -arch=i386 __control87_2(long long ptr ptr)
@ stub __create_locale
@ cdecl __crtCompareStringA(long long str long str long)
@ cdecl __crtCompareStringW(long long wstr long wstr long)
@ cdecl __crtLCMapStringA(long long str long ptr long long long)
@ cdecl __crtLCMapStringW(long long wstr long ptr long long long)
@ cdecl __daylight() MSVCRT___p__daylight
@ cdecl __dllonexit(ptr ptr ptr)
@ cdecl __doserrno() MSVCRT___doserrno
@ cdecl __dstbias() MSVCRT___p__dstbias
@ stub ___fls_getvalue@4
@ stub ___fls_setvalue@8
@ cdecl __fpecode()
@ stub __free_locale
@ stub __get_current_locale
@ stub __get_flsindex
@ stub __get_tlsindex
@ cdecl __getmainargs(ptr ptr ptr long ptr)
@ extern __initenv MSVCRT___initenv
@ cdecl __iob_func() MSVCRT___iob_func
@ cdecl __isascii(long) MSVCRT___isascii
@ cdecl __iscsym(long) MSVCRT___iscsym
@ cdecl __iscsymf(long) MSVCRT___iscsymf
@ stub __iswcsym
@ stub __iswcsymf
# extern __lconv
@ cdecl __lconv_init()
@ cdecl -arch=i386 -norelay __libm_sse2_acos() MSVCRT___libm_sse2_acos
@ cdecl -arch=i386 -norelay __libm_sse2_acosf() MSVCRT___libm_sse2_acosf
@ cdecl -arch=i386 -norelay __libm_sse2_asin() MSVCRT___libm_sse2_asin
@ cdecl -arch=i386 -norelay __libm_sse2_asinf() MSVCRT___libm_sse2_asinf
@ cdecl -arch=i386 -norelay __libm_sse2_atan() MSVCRT___libm_sse2_atan
@ cdecl -arch=i386 -norelay __libm_sse2_atan2() MSVCRT___libm_sse2_atan2
@ cdecl -arch=i386 -norelay __libm_sse2_atanf() MSVCRT___libm_sse2_atanf
@ cdecl -arch=i386 -norelay __libm_sse2_cos() MSVCRT___libm_sse2_cos
@ cdecl -arch=i386 -norelay __libm_sse2_cosf() MSVCRT___libm_sse2_cosf
@ cdecl -arch=i386 -norelay __libm_sse2_exp() MSVCRT___libm_sse2_exp
@ cdecl -arch=i386 -norelay __libm_sse2_expf() MSVCRT___libm_sse2_expf
@ cdecl -arch=i386 -norelay __libm_sse2_log() MSVCRT___libm_sse2_log
@ cdecl -arch=i386 -norelay __libm_sse2_log10() MSVCRT___libm_sse2_log10
@ cdecl -arch=i386 -norelay __libm_sse2_log10f() MSVCRT___libm_sse2_log10f
@ cdecl -arch=i386 -norelay __libm_sse2_logf() MSVCRT___libm_sse2_logf
@ cdecl -arch=i386 -norelay __libm_sse2_pow() MSVCRT___libm_sse2_pow
@ cdecl -arch=i386 -norelay __libm_sse2_powf() MSVCRT___libm_sse2_powf
@ cdecl -arch=i386 -norelay __libm_sse2_sin() MSVCRT___libm_sse2_sin
@ cdecl -arch=i386 -norelay __libm_sse2_sinf() MSVCRT___libm_sse2_sinf
@ cdecl -arch=i386 -norelay __libm_sse2_tan() MSVCRT___libm_sse2_tan
@ cdecl -arch=i386 -norelay __libm_sse2_tanf() MSVCRT___libm_sse2_tanf
@ cdecl __p___argc() MSVCRT___p___argc
@ cdecl __p___argv() MSVCRT___p___argv
@ cdecl __p___wargv() MSVCRT___p___wargv
#@ cdecl __p___initenv()
@ cdecl __p___mb_cur_max()
#@ cdecl __p___winitenv()
#@ cdecl __p__acmdln()
@ cdecl __p__commode()
@ cdecl __p__daylight() MSVCRT___p__daylight
@ cdecl __p__dstbias() MSVCRT___p__dstbias
@ cdecl __p__environ() MSVCRT___p__environ
@ cdecl __p__fmode() MSVCRT__p__fmode
@ cdecl __p__iob() MSVCRT___iob_func
@ stub __p__mbcasemap()
@ cdecl __p__mbctype()
@ cdecl __p__pctype() MSVCRT___p__pctype
#@ cdecl __p__pgmptr() MSVCRT___p__pgmptr
@ stub __p__pwctype()
@ cdecl __p__timezone() MSVCRT___p__timezone
@ cdecl __p__tzname()
#@ cdecl __p__wcmdln()
@ cdecl __p__wenviron() MSVCRT___p__wenviron
#@ cdecl __p__wpgmptr() MSVCRT___p__wpgmptr
@ cdecl __pctype_func() MSVCRT___pctype_func
@ extern __pioinfo ucrtbase.__qemu_native_data__
@ stub __pwctype_func
#@ cdecl __pxcptinfoptrs() MSVCRT___pxcptinfoptrs
@ stub __report_gsfailure
@ stub __set_flsgetvalue
#@ extern __setlc_active MSVCRT___setlc_active
@ cdecl __setusermatherr(ptr) MSVCRT___setusermatherr
@ cdecl __stdio_common_vfprintf(int64 ptr str ptr ptr) MSVCRT__stdio_common_vfprintf
@ cdecl -norelay __stdio_common_vsprintf(int64 ptr long str ptr ptr)
@ cdecl __stdio_common_vsscanf(int64 ptr long str ptr ptr) MSVCRT__stdio_common_vsscanf
@ cdecl __stdio_common_vswprintf(int64 ptr long wstr ptr ptr)
@ stub __strncnt
#@ varargs  __swprintf_l(ptr wstr ptr) MSVCRT___swprintf_l
@ cdecl __sys_errlist()
@ cdecl __sys_nerr()
@ cdecl __threadhandle() kernel32.GetCurrentThread
@ cdecl __threadid() kernel32.GetCurrentThreadId
@ cdecl __timezone() MSVCRT___p__timezone
@ cdecl __toascii(long) MSVCRT___toascii
@ cdecl __tzname() __p__tzname
@ cdecl __unDName(ptr str long ptr ptr long)
@ cdecl __unDNameEx(ptr str long ptr ptr ptr long)
@ stub __unDNameHelper
#@ extern __unguarded_readlc_active MSVCRT___unguarded_readlc_active
#@ cdecl __vswprintf_l(ptr wstr ptr ptr) MSVCRT_vswprintf_l
#@ extern __wargv MSVCRT___wargv
@ cdecl __wcserror(wstr) MSVCRT___wcserror
@ cdecl __wcserror_s(ptr long wstr) MSVCRT___wcserror_s
@ stub __wcsncnt
@ cdecl __wgetmainargs(ptr ptr ptr long ptr)
#@ extern __winitenv MSVCRT___winitenv
#@ cdecl _abnormal_termination()
@ cdecl -ret64 _abs64(int64)
@ cdecl _access(str long) MSVCRT__access
@ cdecl _access_s(str long) MSVCRT__access_s
@ extern _acmdln MSVCRT__acmdln
#@ cdecl _aligned_free(ptr)
#@ cdecl _aligned_malloc(long long)
@ cdecl _aligned_msize(ptr long long)
@ cdecl _aligned_offset_malloc(long long long)
@ cdecl _aligned_offset_realloc(ptr long long long)
@ stub _aligned_offset_recalloc
@ cdecl _aligned_realloc(ptr long long)
@ stub _aligned_recalloc
@ cdecl _amsg_exit(long)
@ cdecl _assert(str str long) MSVCRT__assert
@ cdecl _atodbl(ptr str) MSVCRT__atodbl
@ cdecl _atodbl_l(ptr str ptr) MSVCRT__atodbl_l
@ cdecl _atof_l(str ptr) MSVCRT__atof_l
@ cdecl _atoflt(ptr str) MSVCRT__atoflt
@ cdecl _atoflt_l(ptr str ptr) MSVCRT__atoflt_l
@ cdecl -ret64 _atoi64(str) ntdll._atoi64
@ stub _atoi64_l
#@ cdecl _atoi_l(str ptr) MSVCRT__atoi_l
@ stub _atol_l
@ cdecl _atoldbl(ptr str) MSVCRT__atoldbl
@ stub _atoldbl_l
#@ cdecl _beep(long long) MSVCRT__beep
@ cdecl _beginthread(ptr long ptr) MSVCRT__beginthread
@ cdecl _beginthreadex(ptr long ptr ptr long ptr) MSVCRT__beginthreadex
#@ cdecl _byteswap_uint64(int64)
#@ cdecl _byteswap_ulong(long) MSVCRT__byteswap_ulong
#@ cdecl _byteswap_ushort(long)
#@ cdecl _c_exit() MSVCRT__c_exit
@ cdecl _cabs(long) MSVCRT__cabs
@ cdecl _callnewh(long)
@ cdecl _calloc_crt(long long) MSVCRT_calloc
@ cdecl _cexit() MSVCRT__cexit
@ cdecl _cgets(ptr)
@ stub _cgets_s
@ stub _cgetws
@ stub _cgetws_s
@ cdecl _chdir(str) MSVCRT__chdir
@ cdecl _chdrive(long) MSVCRT__chdrive
@ cdecl _chgsign(double) MSVCRT__chgsign
@ cdecl -arch=arm,x86_64,arm64 _chgsignf(float) MSVCRT__chgsignf
#@ cdecl -arch=i386 -norelay _chkesp()
@ cdecl _chmod(str long) MSVCRT__chmod
@ cdecl _chsize(long long) MSVCRT__chsize
@ cdecl _chsize_s(long int64) MSVCRT__chsize_s
@ cdecl _clearfp()
@ cdecl _close(long) MSVCRT__close
@ cdecl _commit(long) MSVCRT__commit
@ extern _commode MSVCRT__commode
@ cdecl _configthreadlocale(long)
@ cdecl _configure_narrow_argv(long)
@ cdecl _configure_wide_argv(long)
@ cdecl _control87(long long)
@ cdecl _controlfp(long long)
@ cdecl _controlfp_s(ptr long long)
@ cdecl _copysign(double double) MSVCRT__copysign
@ cdecl -arch=arm,x86_64,arm64 _copysignf(float float) MSVCRT__copysignf
#@ varargs _cprintf(str)
@ stub _cprintf_l
@ stub _cprintf_p
@ stub _cprintf_p_l
@ stub _cprintf_s
@ stub _cprintf_s_l
@ cdecl _cputs(str)
@ cdecl _cputws(wstr)
@ cdecl _creat(str long) MSVCRT__creat
@ cdecl _create_locale(long str) MSVCRT__create_locale
@ cdecl -arch=i386 _crt_debugger_hook(long) MSVCRT___crt_debugger_hook
@ cdecl -arch=arm,win64 __crt_debugger_hook(long) MSVCRT___crt_debugger_hook
#@ varargs _cscanf(str)
#@ varargs _cscanf_l(str ptr)
#@ varargs _cscanf_s(str)
#@ varargs _cscanf_s_l(str ptr)
@ cdecl _ctime32(ptr) MSVCRT__ctime32
@ cdecl _ctime32_s(str long ptr) MSVCRT__ctime32_s
@ cdecl _ctime64(ptr) MSVCRT__ctime64
@ cdecl _ctime64_s(str long ptr) MSVCRT__ctime64_s
@ cdecl _cwait(ptr long long)
#@ varargs _cwprintf(wstr)
@ stub _cwprintf_l
@ stub _cwprintf_p
@ stub _cwprintf_p_l
@ stub _cwprintf_s
@ stub _cwprintf_s_l
#@ varargs _cwscanf(wstr)
#@ varargs _cwscanf_l(wstr ptr)
#@ varargs _cwscanf_s(wstr)
#@ varargs _cwscanf_s_l(wstr ptr)
#@ extern _daylight MSVCRT___daylight
@ cdecl _difftime32(long long) MSVCRT__difftime32
@ cdecl _difftime64(int64 int64) MSVCRT__difftime64
@ stub _dosmaperr
#@ extern _dstbias MSVCRT__dstbias
@ cdecl _dup(long) MSVCRT__dup
@ cdecl _dup2(long long) MSVCRT__dup2
@ cdecl _dupenv_s(ptr ptr str)
@ cdecl _ecvt(double long ptr ptr) MSVCRT__ecvt
@ cdecl _ecvt_s(str long double long ptr ptr) MSVCRT__ecvt_s
@ cdecl _encoded_null()
@ cdecl _endthread() MSVCRT__endthread
@ cdecl _endthreadex(long) MSVCRT__endthreadex
@ extern _environ MSVCRT__environ
@ cdecl _eof(long) MSVCRT__eof
@ cdecl _errno() MSVCRT__errno
#@ cdecl -arch=i386 _except_handler2(ptr ptr ptr ptr)
@ cdecl -arch=i386 _except_handler3(ptr ptr ptr ptr)
@ cdecl -arch=i386 _except_handler4_common(ptr ptr ptr ptr ptr ptr)
#@ varargs _execl(str str)
#@ varargs _execle(str str)
#@ varargs _execlp(str str)
#@ varargs _execlpe(str str)
@ cdecl _execv(str ptr)
@ cdecl _execve(str ptr ptr) MSVCRT__execve
@ cdecl _execvp(str ptr)
@ cdecl _execvpe(str ptr ptr)
@ cdecl _exit(long) MSVCRT__exit
@ cdecl _expand(ptr long)
@ cdecl _fclose_nolock(ptr) MSVCRT__fclose_nolock
@ cdecl _fcloseall() MSVCRT__fcloseall
@ cdecl _fcvt(double long ptr ptr) MSVCRT__fcvt
@ cdecl _fcvt_s(ptr long double long ptr ptr) MSVCRT__fcvt_s
@ cdecl _fdopen(long str) MSVCRT__fdopen
@ cdecl _fflush_nolock(ptr) MSVCRT__fflush_nolock
@ cdecl _fgetc_nolock(ptr) MSVCRT__fgetc_nolock
@ cdecl _fgetchar() MSVCRT__fgetchar
@ cdecl _fgetwc_nolock(ptr) MSVCRT__fgetwc_nolock
@ cdecl _fgetwchar() MSVCRT__fgetwchar
@ cdecl _filbuf(ptr) MSVCRT__filbuf
@ cdecl _filelength(long) MSVCRT__filelength
@ cdecl -ret64 _filelengthi64(long) MSVCRT__filelengthi64
@ cdecl _fileno(ptr) MSVCRT__fileno
@ cdecl _findclose(long) MSVCRT__findclose
@ cdecl _findfirst32(str ptr) MSVCRT__findfirst32
@ stub _findfirst32i64
@ cdecl _findfirst64(str ptr) MSVCRT__findfirst64
@ cdecl _findfirst64i32(str ptr) MSVCRT__findfirst64i32
@ cdecl _findnext32(long ptr) MSVCRT__findnext32
@ stub _findnext32i64
@ cdecl _findnext64(long ptr) MSVCRT__findnext64
@ cdecl _findnext64i32(long ptr) MSVCRT__findnext64i32
@ cdecl _finite(double) MSVCRT__finite
@ cdecl -arch=arm,x86_64,arm64 _finitef(float) MSVCRT__finitef
@ cdecl _flsbuf(long ptr) MSVCRT__flsbuf
@ cdecl _flushall() MSVCRT__flushall
@ extern _fmode MSVCRT__fmode
@ cdecl _fpclass(double) MSVCRT__fpclass
# stub -arch=x86_64 _fpclassf
#@ cdecl -arch=i386,x86_64,arm,arm64 _fpieee_flt(long ptr ptr)
@ cdecl _fpreset()
@ stub _fprintf_l
@ stub _fprintf_p
@ stub _fprintf_p_l
@ stub _fprintf_s_l
@ cdecl _fputc_nolock(long ptr) MSVCRT__fputc_nolock
@ cdecl _fputchar(long) MSVCRT__fputchar
@ cdecl _fputwc_nolock(long ptr) MSVCRT__fputwc_nolock
@ cdecl _fputwchar(long) MSVCRT__fputwchar
@ cdecl _fread_nolock(ptr long long ptr) MSVCRT__fread_nolock
@ cdecl _fread_nolock_s(ptr long long long ptr) MSVCRT__fread_nolock_s
@ cdecl _free_locale(ptr) MSVCRT__free_locale
@ stub _freea
@ stub _freea_s
@ stub _freefls
#@ varargs _fscanf_l(ptr str ptr) MSVCRT__fscanf_l
#@ varargs _fscanf_s_l(ptr str ptr) MSVCRT__fscanf_s_l
@ cdecl _fseek_nolock(ptr long long) MSVCRT__fseek_nolock
@ cdecl _fseeki64(ptr int64 long) MSVCRT__fseeki64
@ cdecl _fseeki64_nolock(ptr int64 long) MSVCRT__fseeki64_nolock
@ cdecl _fsopen(str str long) MSVCRT__fsopen
@ cdecl _fstat32(long ptr) MSVCRT__fstat32
@ cdecl _fstat32i64(long ptr) MSVCRT__fstat32i64
@ cdecl _fstat64(long ptr) MSVCRT__fstat64
@ cdecl _fstat64i32(long ptr) MSVCRT__fstat64i32
@ cdecl _ftell_nolock(ptr) MSVCRT__ftell_nolock
@ cdecl -ret64 _ftelli64(ptr) MSVCRT__ftelli64
@ cdecl -ret64 _ftelli64_nolock(ptr) MSVCRT__ftelli64_nolock
@ cdecl _ftime32(ptr) MSVCRT__ftime32
@ cdecl _ftime32_s(ptr) MSVCRT__ftime32_s
@ cdecl _ftime64(ptr) MSVCRT__ftime64
@ cdecl _ftime64_s(ptr) MSVCRT__ftime64_s
@ cdecl -arch=i386 -ret64 _ftol() MSVCRT__ftol
@ cdecl _fullpath(ptr str long) MSVCRT__fullpath
@ cdecl _futime32(long ptr) MSVCRT__futime32
@ cdecl _futime64(long ptr) MSVCRT__futime64
#@ varargs _fwprintf_l(ptr wstr ptr) MSVCRT__fwprintf_l
@ stub _fwprintf_p
@ stub _fwprintf_p_l
@ stub _fwprintf_s_l
@ cdecl _fwrite_nolock(ptr long long ptr) MSVCRT__fwrite_nolock
#@ varargs _fwscanf_l(ptr wstr ptr) MSVCRT__fwscanf_l
#@ varargs _fwscanf_s_l(ptr wstr ptr) MSVCRT__fwscanf_s_l
@ cdecl _gcvt(double long str) MSVCRT__gcvt
@ cdecl _gcvt_s(ptr long  double long) MSVCRT__gcvt_s
@ cdecl _get_current_locale() MSVCRT__get_current_locale
@ cdecl _get_daylight(ptr)
@ cdecl _get_doserrno(ptr) MSVCRT__get_doserrno
@ cdecl _get_dstbias(ptr) MSVCRT__get_dstbias
@ cdecl _get_errno(ptr)
@ cdecl _get_fmode(ptr) MSVCRT__get_fmode
@ cdecl _get_heap_handle()
@ cdecl _get_initial_narrow_environment()
@ cdecl _get_initial_wide_environment()
@ cdecl _get_invalid_parameter_handler() MSVCRT__get_invalid_parameter_handler
@ cdecl _get_osfhandle(long) MSVCRT__get_osfhandle
#@ cdecl _get_output_format() MSVCRT__get_output_format
@ cdecl _get_pgmptr(ptr)
@ cdecl _get_printf_count_output() MSVCRT__get_printf_count_output
#@ cdecl _get_purecall_handler()
#@ cdecl _get_terminate() MSVCRT__get_terminate
@ cdecl _get_timezone(ptr)
@ cdecl _get_tzname(ptr str long long) MSVCRT__get_tzname
#@ cdecl _get_unexpected() MSVCRT__get_unexpected
@ cdecl _get_wpgmptr(ptr)
@ cdecl _getc_nolock(ptr) MSVCRT__fgetc_nolock
@ cdecl _getch()
@ cdecl _getch_nolock()
@ cdecl _getche()
@ cdecl _getche_nolock()
@ cdecl _getcwd(str long) MSVCRT__getcwd
@ cdecl _getdcwd(long str long) MSVCRT__getdcwd
@ stub _getdcwd_nolock
@ cdecl _getdiskfree(long ptr) MSVCRT__getdiskfree
@ cdecl _getdllprocaddr(long str long) MSVCRT__getdllprocaddr
@ cdecl _getdrive() MSVCRT__getdrive
@ cdecl _getdrives() kernel32.GetLogicalDrives
@ cdecl _getmaxstdio() MSVCRT__getmaxstdio
@ cdecl _getmbcp()
@ cdecl _getpid() _getpid
@ cdecl _getptd() MSVCRT__getptd
@ stub _getsystime(ptr)
@ cdecl _getw(ptr) MSVCRT__getw
@ cdecl _getwc_nolock(ptr) MSVCRT__fgetwc_nolock
@ cdecl _getwch()
@ cdecl _getwch_nolock()
@ cdecl _getwche()
@ cdecl _getwche_nolock()
@ cdecl _getws(ptr) MSVCRT__getws
@ stub _getws_s
@ cdecl -arch=i386 _global_unwind2(ptr)
@ cdecl _gmtime32(ptr) MSVCRT__gmtime32
@ cdecl _gmtime32_s(ptr ptr) MSVCRT__gmtime32_s
@ cdecl _gmtime64(ptr) MSVCRT__gmtime64
@ cdecl _gmtime64_s(ptr ptr) MSVCRT__gmtime64_s
@ cdecl _heapadd(ptr long)
@ cdecl _heapchk()
@ cdecl _heapmin()
@ cdecl _heapset(long)
@ stub _heapused(ptr ptr)
#@ cdecl _heapwalk(ptr)
@ cdecl _hypot(double double)
@ cdecl _hypotf(float float) MSVCRT__hypotf
@ cdecl _i64toa(int64 ptr long) ntdll._i64toa
@ cdecl _i64toa_s(int64 ptr long long) MSVCRT__i64toa_s
@ cdecl _i64tow(int64 ptr long) ntdll._i64tow
@ cdecl _i64tow_s(int64 ptr long long) MSVCRT__i64tow_s
@ cdecl _initialize_narrow_environment()
@ cdecl _initialize_wide_environment()
@ stub _initptd
@ cdecl _initterm(ptr ptr)
@ cdecl _initterm_e(ptr ptr)
@ stub -arch=i386 _inp(long)
@ stub -arch=i386 _inpd(long)
@ stub -arch=i386 _inpw(long)
#@ cdecl _invalid_parameter(wstr wstr wstr long long) MSVCRT__invalid_parameter
@ cdecl _invalid_parameter_noinfo()
@ cdecl _invalid_parameter_noinfo_noreturn()
@ cdecl _invoke_watson() MSVCRT_generic_stub
@ extern -arch=i386 _iob guest_iob
@ extern -arch=x86_64 _iob msvcrt.__qemu_native_data__
@ cdecl _isalnum_l(long ptr) MSVCRT__isalnum_l
@ cdecl _isalpha_l(long ptr) MSVCRT__isalpha_l
@ cdecl _isatty(long) MSVCRT__isatty
@ cdecl _iscntrl_l(long ptr) MSVCRT__iscntrl_l
@ cdecl _isctype(long long) MSVCRT__isctype
@ cdecl _isctype_l(long long ptr) MSVCRT__isctype_l
@ cdecl _isdigit_l(long ptr) MSVCRT__isdigit_l
@ cdecl _isgraph_l(long ptr) MSVCRT__isgraph_l
@ cdecl _isleadbyte_l(long ptr) MSVCRT__isleadbyte_l
@ cdecl _islower_l(long ptr) MSVCRT__islower_l
@ stub _ismbbalnum(long)
@ stub _ismbbalnum_l
@ stub _ismbbalpha(long)
@ stub _ismbbalpha_l
@ stub _ismbbgraph(long)
@ stub _ismbbgraph_l
@ stub _ismbbkalnum(long)
@ stub _ismbbkalnum_l
@ cdecl _ismbbkana(long)
@ stub _ismbbkana_l
@ stub _ismbbkprint(long)
@ stub _ismbbkprint_l
@ stub _ismbbkpunct(long)
@ stub _ismbbkpunct_l
@ cdecl _ismbblead(long)
@ cdecl _ismbblead_l(long ptr)
@ stub _ismbbprint(long)
@ stub _ismbbprint_l
@ stub _ismbbpunct(long)
@ stub _ismbbpunct_l
@ cdecl _ismbbtrail(long)
@ stub _ismbbtrail_l
@ cdecl _ismbcalnum(long)
@ stub _ismbcalnum_l
@ cdecl _ismbcalpha(long)
@ stub _ismbcalpha_l
@ cdecl _ismbcdigit(long)
@ stub _ismbcdigit_l
@ cdecl _ismbcgraph(long)
@ stub _ismbcgraph_l
@ cdecl _ismbchira(long)
@ stub _ismbchira_l
@ cdecl _ismbckata(long)
@ stub _ismbckata_l
#@ cdecl _ismbcl0(long)
@ stub _ismbcl0_l
@ stub _ismbcl1(long)
@ stub _ismbcl1_l
@ stub _ismbcl2(long)
@ stub _ismbcl2_l
@ cdecl _ismbclegal(long)
@ stub _ismbclegal_l
@ cdecl _ismbclower(long)
@ stub _ismbclower_l
@ cdecl _ismbcprint(long)
@ stub _ismbcprint_l
@ cdecl _ismbcpunct(long)
@ stub _ismbcpunct_l
@ cdecl _ismbcspace(long)
@ stub _ismbcspace_l
@ cdecl _ismbcsymbol(long)
@ stub _ismbcsymbol_l
@ cdecl _ismbcupper(long)
@ stub _ismbcupper_l
@ cdecl _ismbslead(ptr ptr)
@ stub _ismbslead_l
@ cdecl _ismbstrail(ptr ptr)
@ stub _ismbstrail_l
@ cdecl _isnan(double) MSVCRT__isnan
@ cdecl -arch=x86_64 _isnanf(float) MSVCRT__isnanf
@ cdecl _isprint_l(long ptr) MSVCRT__isprint_l
@ stub _ispunct_l
@ cdecl _isspace_l(long ptr) MSVCRT__isspace_l
@ cdecl _isupper_l(long ptr) MSVCRT__isupper_l
@ stub _iswalnum_l
@ cdecl _iswalpha_l(long ptr) MSVCRT__iswalpha_l
@ stub _iswcntrl_l
@ stub _iswcsym_l
@ stub _iswcsymf_l
@ cdecl _iswctype_l(long long ptr) MSVCRT__iswctype_l
@ cdecl _iswdigit_l(long ptr) MSVCRT__iswdigit_l
@ stub _iswgraph_l
@ stub _iswlower_l
@ stub _iswprint_l
@ cdecl _iswpunct_l(long ptr) MSVCRT__iswpunct_l
@ cdecl _iswspace_l(long ptr) MSVCRT__iswspace_l
@ stub _iswupper_l
@ stub _iswxdigit_l
@ cdecl _isxdigit_l(long ptr) MSVCRT__isxdigit_l
@ cdecl _itoa(long ptr long) MSVCRT__itoa
@ cdecl _itoa_s(long ptr long long) MSVCRT__itoa_s
@ cdecl _itow(long ptr long) ntdll._itow
@ cdecl _itow_s(long ptr long long) MSVCRT__itow_s
@ cdecl _j0(double) MSVCRT__j0
@ cdecl _j1(double) MSVCRT__j1
@ cdecl _jn(long double) MSVCRT__jn
@ cdecl _kbhit()
#@ cdecl _lfind(ptr ptr ptr long ptr)
#@ cdecl _lfind_s(ptr ptr ptr long ptr ptr)
@ cdecl _loaddll(str)
@ cdecl -arch=x86_64 _local_unwind(ptr ptr)
#@ cdecl -arch=i386 _local_unwind2(ptr long)
#@ cdecl -arch=i386 _local_unwind4(ptr ptr long)
@ cdecl _localtime32(ptr) MSVCRT__localtime32
#@ cdecl _localtime32_s(ptr ptr)
@ cdecl _localtime64(ptr) MSVCRT__localtime64
#@ cdecl _localtime64_s(ptr ptr)
@ cdecl _lock(long)
@ cdecl _lock_file(ptr) MSVCRT__lock_file
@ cdecl _locking(long long long) MSVCRT__locking
@ cdecl _logb(double) MSVCRT__logb
@ cdecl -arch=arm,x86_64,arm64 _logbf(float) MSVCRT__logbf
@ cdecl -arch=i386 _longjmpex(ptr long) MSVCRT_longjmp
@ cdecl _lrotl(long long) MSVCRT__lrotl
@ cdecl _lrotr(long long) MSVCRT__lrotr
#@ cdecl _lsearch(ptr ptr ptr long ptr)
@ stub _lsearch_s
@ cdecl _lseek(long long long) MSVCRT__lseek
@ cdecl -ret64 _lseeki64(long int64 long) MSVCRT__lseeki64
@ cdecl _ltoa(long ptr long) ntdll._ltoa
@ cdecl _ltoa_s(long ptr long long) MSVCRT__ltoa_s
@ cdecl _ltow(long ptr long) ntdll._ltow
@ cdecl _ltow_s(long ptr long long) MSVCRT__ltow_s
@ cdecl _makepath(ptr str str str str) MSVCRT__makepath
@ cdecl _makepath_s(ptr long str str str str) MSVCRT__makepath_s
@ cdecl _malloc_crt(long) MSVCRT_malloc
@ cdecl _mbbtombc(long)
@ stub _mbbtombc_l
@ cdecl _mbbtype(long long)
@ stub _mbbtype_l
# extern _mbcasemap
@ cdecl _mbccpy(ptr ptr)
#@ cdecl _mbccpy_l(ptr ptr ptr)
#@ cdecl _mbccpy_s(ptr long ptr ptr)
#@ cdecl _mbccpy_s_l(ptr long ptr ptr ptr)
@ cdecl _mbcjistojms(long)
@ stub _mbcjistojms_l
@ cdecl _mbcjmstojis(long)
@ stub _mbcjmstojis_l
@ cdecl _mbclen(ptr)
@ stub _mbclen_l
@ cdecl _mbctohira(long)
@ stub _mbctohira_l
@ cdecl _mbctokata(long)
@ stub _mbctokata_l
@ cdecl _mbctolower(long)
@ stub _mbctolower_l
@ cdecl _mbctombb(long)
@ stub _mbctombb_l
@ cdecl _mbctoupper(long)
@ stub _mbctoupper_l
#@ extern _mbctype MSVCRT_mbctype
@ stub _mblen_l
@ cdecl _mbsbtype(str long)
@ stub _mbsbtype_l
@ cdecl _mbscat_s(ptr long str)
@ cdecl _mbscat_s_l(ptr long str ptr)
@ cdecl _mbschr(str long)
@ stub _mbschr_l
@ cdecl _mbscmp(str str)
@ stub _mbscmp_l
@ cdecl _mbscoll(str str)
@ cdecl _mbscoll_l(str str ptr)
@ cdecl _mbscpy_s(ptr long str)
@ cdecl _mbscpy_s_l(ptr long str ptr)
@ cdecl _mbscspn(str str)
@ stub _mbscspn_l
@ cdecl _mbsdec(ptr ptr)
@ stub _mbsdec_l
@ cdecl _mbsicmp(str str)
@ stub _mbsicmp_l
@ cdecl _mbsicoll(str str)
@ cdecl _mbsicoll_l(str str ptr)
@ cdecl _mbsinc(str)
@ stub _mbsinc_l
@ cdecl _mbslen(str)
#@ cdecl _mbslen_l(str ptr)
@ cdecl _mbslwr(str)
@ stub _mbslwr_l
@ cdecl _mbslwr_s(str long)
@ stub _mbslwr_s_l
@ cdecl _mbsnbcat(str str long)
@ stub _mbsnbcat_l
@ cdecl _mbsnbcat_s(str long ptr long)
@ stub _mbsnbcat_s_l
@ cdecl _mbsnbcmp(str str long)
@ stub _mbsnbcmp_l
@ cdecl _mbsnbcnt(ptr long)
@ stub _mbsnbcnt_l
@ cdecl _mbsnbcoll(str str long)
@ cdecl _mbsnbcoll_l(str str long ptr)
@ cdecl _mbsnbcpy(ptr str long)
@ stub _mbsnbcpy_l
@ cdecl _mbsnbcpy_s(ptr long str long)
@ cdecl _mbsnbcpy_s_l(ptr long str long ptr)
@ cdecl _mbsnbicmp(str str long)
@ stub _mbsnbicmp_l
@ cdecl _mbsnbicoll(str str long)
@ cdecl _mbsnbicoll_l(str str long ptr)
@ cdecl _mbsnbset(ptr long long)
@ stub _mbsnbset_l
@ stub _mbsnbset_s
@ stub _mbsnbset_s_l
@ cdecl _mbsncat(str str long)
@ stub _mbsncat_l
@ stub _mbsncat_s
@ stub _mbsncat_s_l
@ cdecl _mbsnccnt(str long)
@ stub _mbsnccnt_l
@ cdecl _mbsncmp(str str long)
@ stub _mbsncmp_l
@ stub _mbsncoll(str str long)
@ stub _mbsncoll_l
@ cdecl _mbsncpy(ptr str long)
@ stub _mbsncpy_l
@ stub _mbsncpy_s
@ stub _mbsncpy_s_l
@ cdecl _mbsnextc(str)
@ stub _mbsnextc_l
@ cdecl _mbsnicmp(str str long)
@ stub _mbsnicmp_l
@ stub _mbsnicoll(str str long)
@ stub _mbsnicoll_l
@ cdecl _mbsninc(str long)
@ stub _mbsninc_l
#@ cdecl _mbsnlen(str long)
#@ cdecl _mbsnlen_l(str long ptr)
@ cdecl _mbsnset(ptr long long)
@ stub _mbsnset_l
@ stub _mbsnset_s
@ stub _mbsnset_s_l
@ cdecl _mbspbrk(str str)
@ stub _mbspbrk_l
@ cdecl _mbsrchr(str long)
@ stub _mbsrchr_l
@ cdecl _mbsrev(str)
@ stub _mbsrev_l
@ cdecl _mbsset(ptr long)
@ stub _mbsset_l
@ stub _mbsset_s
@ stub _mbsset_s_l
@ cdecl _mbsspn(str str)
@ stub _mbsspn_l
@ cdecl _mbsspnp(str str)
@ stub _mbsspnp_l
@ cdecl _mbsstr(str str)
@ stub _mbsstr_l
@ cdecl _mbstok(str str)
@ cdecl _mbstok_l(str str ptr)
@ cdecl _mbstok_s(str str ptr)
@ cdecl _mbstok_s_l(str str ptr ptr)
@ cdecl _mbstowcs_l(ptr str long ptr) MSVCRT__mbstowcs_l
@ cdecl _mbstowcs_s_l(ptr ptr long str long ptr) MSVCRT__mbstowcs_s_l
@ cdecl _mbstrlen(str) MSVCRT__mbstrlen
@ cdecl _mbstrlen_l(str ptr) MSVCRT__mbstrlen_l
@ stub _mbstrnlen
@ stub _mbstrnlen_l
@ cdecl _mbsupr(str)
@ stub _mbsupr_l
@ cdecl _mbsupr_s(str long)
@ stub _mbsupr_s_l
@ cdecl _mbtowc_l(ptr str long ptr) MSVCRT_mbtowc_l
@ cdecl _memccpy(ptr ptr long long) ntdll._memccpy
#@ cdecl _memicmp(str str long) MSVCRT__memicmp
#@ cdecl _memicmp_l(str str long ptr) MSVCRT__memicmp_l
@ cdecl _mkdir(str) MSVCRT__mkdir
@ cdecl _mkgmtime32(ptr) MSVCRT__mkgmtime32
@ cdecl _mkgmtime64(ptr) MSVCRT__mkgmtime64
@ cdecl _mktemp(str) MSVCRT__mktemp
@ cdecl _mktemp_s(str long) MSVCRT__mktemp_s
@ cdecl _mktime32(ptr) MSVCRT__mktime32
@ cdecl _mktime64(ptr) MSVCRT__mktime64
@ cdecl _msize(ptr)
@ cdecl _nextafter(double double) MSVCRT__nextafter
@ cdecl -arch=x86_64 _nextafterf(float float) MSVCRT__nextafterf
@ cdecl _onexit(ptr) MSVCRT__onexit
@ varargs _open(str long) MSVCRT__open
@ cdecl _open_osfhandle(long long) MSVCRT__open_osfhandle
@ stub -arch=i386 _outp(long long)
@ stub -arch=i386 _outpd(long long)
@ stub -arch=i386 _outpw(long long)
@ cdecl _pclose(ptr) MSVCRT__pclose
@ extern _pctype ucrtbase.__qemu_native_data__
#@ extern _pgmptr MSVCRT__pgmptr
@ cdecl _pipe(ptr long long) MSVCRT__pipe
@ cdecl _popen(str str) MSVCRT__popen
@ stub _printf_l
@ stub _printf_p
@ stub _printf_p_l
@ stub _printf_s_l
@ cdecl _purecall()
@ cdecl _putc_nolock(long ptr) MSVCRT__fputc_nolock
@ cdecl _putch(long)
@ cdecl _putch_nolock(long)
@ cdecl _putenv(str) MSVCRT__putenv
@ cdecl _putenv_s(str str)
@ cdecl _putw(long ptr) MSVCRT__putw
@ cdecl _putwc_nolock(long ptr) MSVCRT__fputwc_nolock
@ cdecl _putwch(long)
@ cdecl _putwch_nolock(long)
@ cdecl _putws(wstr) MSVCRT__putws
# extern _pwctype
@ cdecl _read(long ptr long) MSVCRT__read
@ cdecl _realloc_crt(ptr long) MSVCRT_realloc
@ cdecl _recalloc(ptr long long)
@ stub _recalloc_crt
#@ cdecl _resetstkoflw() MSVCRT__resetstkoflw
@ cdecl _rmdir(str) MSVCRT__rmdir
@ cdecl _rmtmp() MSVCRT__rmtmp
@ cdecl _rotl(long long) MSVCRT__rotl
@ cdecl -ret64 _rotl64(int64 long)
@ cdecl _rotr(long long) MSVCRT__rotr
@ cdecl -ret64 _rotr64(int64 long)
@ cdecl _scalb(double long) MSVCRT__scalb
@ cdecl -arch=x86_64 _scalbf(float long) MSVCRT__scalbf
#@ varargs _scanf_l(str ptr) MSVCRT__scanf_l
#@ varargs _scanf_s_l(str ptr) MSVCRT__scanf_s_l
#@ varargs _scprintf(str) MSVCRT__scprintf
@ stub _scprintf_l
@ stub _scprintf_p
@ stub _scprintf_p_l
#@ varargs _scwprintf(wstr) MSVCRT__scwprintf
@ stub _scwprintf_l
@ stub _scwprintf_p
@ stub _scwprintf_p_l
@ cdecl _searchenv(str str ptr) MSVCRT__searchenv
@ cdecl _searchenv_s(str str ptr long) MSVCRT__searchenv_s
#@ stdcall -arch=i386 _seh_longjmp_unwind4(ptr)
#@ stdcall -arch=i386 _seh_longjmp_unwind(ptr)
@ cdecl _set_SSE2_enable(long) MSVCRT__set_SSE2_enable
#@ cdecl _set_abort_behavior(long long) MSVCRT__set_abort_behavior
@ cdecl _set_app_type(long) MSVCRT___set_app_type
@ cdecl _set_controlfp(long long)
@ cdecl _set_doserrno(long) MSVCRT__set_doserrno
@ cdecl _set_errno(long)
@ cdecl _set_error_mode(long) MSVCRT__set_error_mode
@ cdecl _set_fmode(long) MSVCRT__set_fmode
@ cdecl _set_invalid_parameter_handler(ptr) MSVCRT__set_invalid_parameter_handler
@ stub _set_malloc_crt_max_wait
#@ cdecl _set_output_format(long) MSVCRT__set_output_format
@ cdecl _set_printf_count_output(long) MSVCRT__set_printf_count_output
#@ cdecl _set_purecall_handler(ptr)
@ cdecl _seterrormode(long) MSVCRT__seterrormode
@ cdecl -arch=i386,x86_64,arm,arm64 -norelay _setjmp(ptr) MSVCRT__setjmp
@ cdecl -arch=i386 -norelay _setjmp3(ptr long) MSVCRT__setjmp3
@ cdecl -arch=x86_64,arm -norelay _setjmpex(ptr ptr) MSVCRT__setjmpex
@ cdecl _setmaxstdio(long) MSVCRT__setmaxstdio
@ cdecl _setmbcp(long)
@ cdecl _setmode(long long) MSVCRT__setmode
@ stub _setsystime(ptr long)
#@ cdecl _sleep(long) MSVCRT__sleep
@ varargs _snprintf(ptr long str) MSVCRT__snprintf
@ stub _snprintf_c
@ stub _snprintf_c_l
#@ varargs _snprintf_l(ptr long str ptr) MSVCRT__snprintf_l
@ varargs _snprintf_s(ptr long long str) MSVCRT__snprintf_s
@ stub _snprintf_s_l
@ varargs _snscanf(str long str) MSVCRT__snscanf
#@ varargs _snscanf_l(str long str ptr) MSVCRT__snscanf_l
#@ varargs _snscanf_s(str long str) MSVCRT__snscanf_s
#@ varargs _snscanf_s_l(str long str ptr) MSVCRT__snscanf_s_l
@ varargs _snwprintf(ptr long wstr) MSVCRT__snwprintf
#@ varargs _snwprintf_l(ptr long wstr ptr) MSVCRT__snwprintf_l
#@ varargs _snwprintf_s(ptr long long wstr) MSVCRT__snwprintf_s
#@ varargs _snwprintf_s_l(ptr long long wstr ptr) MSVCRT__snwprintf_s_l
@ varargs _snwscanf(wstr long wstr) MSVCRT__snwscanf
#@ varargs _snwscanf_l(wstr long wstr ptr) MSVCRT__snwscanf_l
#@ varargs _snwscanf_s(wstr long wstr) MSVCRT__snwscanf_s
#@ varargs _snwscanf_s_l(wstr long wstr ptr) MSVCRT__snwscanf_s_l
#@ varargs _sopen(str long long) MSVCRT__sopen
@ cdecl _sopen_s(ptr str long long long) MSVCRT__sopen_s
#@ varargs _spawnl(long str str)
#@ varargs _spawnle(long str str)
#@ varargs _spawnlp(long str str)
#@ varargs _spawnlpe(long str str)
@ cdecl _spawnv(long str ptr) MSVCRT__spawnv
@ cdecl _spawnve(long str ptr ptr) MSVCRT__spawnve
@ cdecl _spawnvp(long str ptr) MSVCRT__spawnvp
@ cdecl _spawnvpe(long str ptr ptr) MSVCRT__spawnvpe
@ cdecl _splitpath(str ptr ptr ptr ptr) MSVCRT__splitpath
@ cdecl _splitpath_s(str ptr long ptr long ptr long ptr long) MSVCRT__splitpath_s
#@ varargs _sprintf_l(ptr str ptr) MSVCRT_sprintf_l
#@ varargs _sprintf_p(ptr long str) MSVCRT__sprintf_p
#@ varargs _sprintf_p_l(ptr long str ptr) MSVCRT_sprintf_p_l
#@ varargs _sprintf_s_l(ptr long str ptr) MSVCRT_sprintf_s_l
#@ varargs _sscanf_l(str str ptr) MSVCRT__sscanf_l
#@ varargs _sscanf_s_l(str str ptr) MSVCRT__sscanf_s_l
@ cdecl _stat32(str ptr) MSVCRT__stat32
@ cdecl _stat32i64(str ptr) MSVCRT__stat32i64
@ cdecl _stat64(str ptr) MSVCRT__stat64
@ cdecl _stat64i32(str ptr) MSVCRT__stat64i32
@ cdecl _statusfp()
@ cdecl -arch=i386 _statusfp2(ptr ptr)
@ cdecl _strcoll_l(str str ptr) MSVCRT_strcoll_l
@ cdecl _strdate(ptr) MSVCRT__strdate
@ cdecl _strdate_s(ptr long)
@ cdecl _strdup(str) MSVCRT__strdup
@ cdecl _strerror(long) MSVCRT__strerror
@ stub _strerror_s
@ cdecl _strftime_l(ptr long str ptr ptr) MSVCRT__strftime_l
@ cdecl _stricmp(str str) MSVCRT__stricmp
#@ cdecl _stricmp_l(str str ptr) MSVCRT__stricmp_l
@ cdecl _stricoll(str str) MSVCRT__stricoll
@ cdecl _stricoll_l(str str ptr) MSVCRT__stricoll_l
@ cdecl _strlwr(str) MSVCRT__strlwr
@ cdecl _strlwr_l(str ptr)
@ cdecl _strlwr_s(ptr long) MSVCRT__strlwr_s
@ cdecl _strlwr_s_l(ptr long ptr) MSVCRT__strlwr_s_l
@ cdecl _strncoll(str str long) MSVCRT__strncoll
@ cdecl _strncoll_l(str str long ptr) MSVCRT__strncoll_l
@ cdecl _strnicmp(str str long) MSVCRT__strnicmp
#@ cdecl _strnicmp_l(str str long ptr) MSVCRT__strnicmp_l
@ cdecl _strnicoll(str str long) MSVCRT__strnicoll
@ cdecl _strnicoll_l(str str long ptr) MSVCRT__strnicoll_l
@ cdecl _strnset(str long long) MSVCRT__strnset
@ cdecl _strnset_s(str long long long) MSVCRT__strnset_s
@ cdecl _strrev(str) MSVCRT__strrev
@ cdecl _strset(str long)
@ stub _strset_s
@ cdecl _strtime(ptr) MSVCRT__strtime
@ cdecl _strtime_s(ptr long)
@ cdecl _strtod_l(str ptr ptr) MSVCRT_strtod_l
@ cdecl -ret64 _strtoi64(str ptr long) MSVCRT__strtoi64
@ cdecl -ret64 _strtoi64_l(str ptr long ptr) MSVCRT__strtoi64_l
@ cdecl _strtol_l(str ptr long ptr) MSVCRT__strtol_l
@ cdecl -ret64 _strtoui64(str ptr long) MSVCRT__strtoui64
@ cdecl -ret64 _strtoui64_l(str ptr long ptr) MSVCRT__strtoui64_l
@ cdecl _strtoul_l(str ptr long ptr) MSVCRT_strtoul_l
@ cdecl _strupr(str) MSVCRT__strupr
@ cdecl _strupr_l(str ptr) MSVCRT__strupr_l
@ cdecl _strupr_s(str long) MSVCRT__strupr_s
@ cdecl _strupr_s_l(str long ptr) MSVCRT__strupr_s_l
@ cdecl _strxfrm_l(ptr str long ptr) MSVCRT__strxfrm_l
@ cdecl _swab(str str long) MSVCRT__swab
#@ varargs _swprintf(ptr wstr) MSVCRT_swprintf
@ stub _swprintf_c
@ stub _swprintf_c_l
@ stub _swprintf_p
#@ varargs _swprintf_p_l(ptr long wstr ptr) MSVCRT_swprintf_p_l
#@ varargs _swprintf_s_l(ptr long wstr ptr) MSVCRT__swprintf_s_l
#@ varargs _swscanf_l(wstr wstr ptr) MSVCRT__swscanf_l
#@ varargs _swscanf_s_l(wstr wstr ptr) MSVCRT__swscanf_s_l
#@ extern _sys_errlist MSVCRT__sys_errlist
#@ extern _sys_nerr MSVCRT__sys_nerr
@ cdecl _tell(long) MSVCRT__tell
@ cdecl -ret64 _telli64(long)
@ cdecl _tempnam(str str) MSVCRT__tempnam
@ cdecl _time32(ptr) MSVCRT__time32
@ cdecl _time64(ptr) MSVCRT__time64
#@ extern _timezone MSVCRT___timezone
@ cdecl _tolower(long) MSVCRT__tolower
@ cdecl _tolower_l(long ptr) MSVCRT__tolower_l
@ cdecl _toupper(long) MSVCRT__toupper
@ cdecl _toupper_l(long ptr) MSVCRT__toupper_l
@ cdecl _towlower_l(long ptr) MSVCRT__towlower_l
@ cdecl _towupper_l(long ptr) MSVCRT__towupper_l
#@ extern _tzname MSVCRT__tzname
@ cdecl _tzset() MSVCRT__tzset
@ cdecl _ui64toa(int64 ptr long) ntdll._ui64toa
@ cdecl _ui64toa_s(int64 ptr long long) MSVCRT__ui64toa_s
@ cdecl _ui64tow(int64 ptr long) ntdll._ui64tow
@ cdecl _ui64tow_s(int64 ptr long long) MSVCRT__ui64tow_s
@ cdecl _ultoa(long ptr long) ntdll._ultoa
@ cdecl _ultoa_s(long ptr long long) MSVCRT__ultoa_s
@ cdecl _ultow(long ptr long) ntdll._ultow
@ cdecl _ultow_s(long ptr long long) MSVCRT__ultow_s
@ cdecl _umask(long) MSVCRT__umask
@ stub _umask_s
@ cdecl _ungetc_nolock(long ptr) MSVCRT__ungetc_nolock
@ cdecl _ungetch(long)
@ cdecl _ungetch_nolock(long)
@ cdecl _ungetwc_nolock(long ptr) MSVCRT__ungetwc_nolock
@ cdecl _ungetwch(long)
@ cdecl _ungetwch_nolock(long)
@ cdecl _unlink(str) MSVCRT__unlink
@ cdecl _unloaddll(long)
@ cdecl _unlock(long)
@ cdecl _unlock_file(ptr) MSVCRT__unlock_file
@ cdecl _utime32(str ptr) MSVCRT__utime32
@ cdecl _utime64(str ptr) MSVCRT__utime64
#@ cdecl _vcprintf(str ptr)
@ stub _vcprintf_l
@ stub _vcprintf_p
@ stub _vcprintf_p_l
@ stub _vcprintf_s
@ stub _vcprintf_s_l
#@ cdecl _vcwprintf(wstr ptr)
@ stub _vcwprintf_l
@ stub _vcwprintf_p
@ stub _vcwprintf_p_l
@ stub _vcwprintf_s
@ stub _vcwprintf_s_l
#@ cdecl _vfprintf_l(ptr str ptr ptr) MSVCRT__vfprintf_l
#@ cdecl _vfprintf_p(ptr str ptr) MSVCRT__vfprintf_p
#@ cdecl _vfprintf_p_l(ptr str ptr ptr) MSVCRT__vfprintf_p_l
#@ cdecl _vfprintf_s_l(ptr str ptr ptr) MSVCRT__vfprintf_s_l
#@ cdecl _vfwprintf_l(ptr wstr ptr ptr) MSVCRT__vfwprintf_l
#@ cdecl _vfwprintf_p(ptr wstr ptr) MSVCRT__vfwprintf_p
#@ cdecl _vfwprintf_p_l(ptr wstr ptr ptr) MSVCRT__vfwprintf_p_l
#@ cdecl _vfwprintf_s_l(ptr wstr ptr ptr) MSVCRT__vfwprintf_s_l
@ stub _vprintf_l
@ stub _vprintf_p
@ stub _vprintf_p_l
@ stub _vprintf_s_l
@ cdecl _vscprintf(str ptr) MSVCRT__vscprintf
@ stub _vscprintf_l
#@ cdecl _vscprintf_p(str ptr) MSVCRT__vscprintf_p
#@ cdecl _vscprintf_p_l(str ptr ptr) MSVCRT__vscprintf_p_l
@ cdecl _vscwprintf(wstr ptr) MSVCRT__vscwprintf
#@ cdecl _vscwprintf_l(wstr ptr ptr) MSVCRT__vscwprintf_l
#@ cdecl _vscwprintf_p(wstr ptr) MSVCRT__vscwprintf_p
#@ cdecl _vscwprintf_p_l(wstr ptr ptr) MSVCRT__vscwprintf_p_l
@ cdecl _vsnprintf(ptr long str ptr) MSVCRT__vsnprintf
@ cdecl _vsnprintf_c(ptr long str ptr) MSVCRT__vsnprintf
#@ cdecl _vsnprintf_c_l(ptr long str ptr ptr) MSVCRT_vsnprintf_l
#@ cdecl _vsnprintf_l(ptr long str ptr ptr) MSVCRT_vsnprintf_l
#@ cdecl _vsnprintf_s(ptr long long str ptr) MSVCRT_vsnprintf_s
#@ cdecl _vsnprintf_s_l(ptr long long str ptr ptr) MSVCRT_vsnprintf_s_l
@ cdecl _vsnwprintf(ptr long wstr ptr) MSVCRT__vsnwprintf
#@ cdecl _vsnwprintf_l(ptr long wstr ptr ptr) MSVCRT_vsnwprintf_l
#@ cdecl _vsnwprintf_s(ptr long long wstr ptr) MSVCRT_vsnwprintf_s
#@ cdecl _vsnwprintf_s_l(ptr long long wstr ptr ptr) MSVCRT_vsnwprintf_s_l
#@ cdecl _vsprintf_l(ptr str ptr ptr) MSVCRT_vsprintf_l
#@ cdecl _vsprintf_p(ptr long str ptr) MSVCRT_vsprintf_p
#@ cdecl _vsprintf_p_l(ptr long str ptr ptr) MSVCRT_vsprintf_p_l
#@ cdecl _vsprintf_s_l(ptr long str ptr ptr) MSVCRT_vsprintf_s_l
@ cdecl _vswprintf(ptr wstr ptr) MSVCRT_vswprintf
@ cdecl _vswprintf_c(ptr long wstr ptr) MSVCRT__vsnwprintf
#@ cdecl _vswprintf_c_l(ptr long wstr ptr ptr) MSVCRT_vsnwprintf_l
#@ cdecl _vswprintf_l(ptr wstr ptr ptr) MSVCRT_vswprintf_l
#@ cdecl _vswprintf_p(ptr long wstr ptr) MSVCRT__vswprintf_p
#@ cdecl _vswprintf_p_l(ptr long wstr ptr ptr) MSVCRT_vswprintf_p_l
#@ cdecl _vswprintf_s_l(ptr long wstr ptr ptr) MSVCRT_vswprintf_s_l
@ stub _vwprintf_l
@ stub _vwprintf_p
@ stub _vwprintf_p_l
@ stub _vwprintf_s_l
@ cdecl _waccess(wstr long) MSVCRT__waccess
@ cdecl _waccess_s(wstr long) MSVCRT__waccess_s
@ cdecl _wasctime(ptr) MSVCRT__wasctime
@ cdecl _wasctime_s(ptr long ptr) MSVCRT__wasctime_s
@ cdecl _wassert(wstr wstr long) MSVCRT__wassert
@ cdecl _wchdir(wstr) MSVCRT__wchdir
@ cdecl _wchmod(wstr long) MSVCRT__wchmod
@ extern _wcmdln MSVCRT__wcmdln
@ cdecl _wcreat(wstr long) MSVCRT__wcreat
@ cdecl _wcscoll_l(wstr wstr ptr) MSVCRT__wcscoll_l
@ cdecl _wcsdup(wstr) MSVCRT__wcsdup
@ cdecl _wcserror(long) MSVCRT__wcserror
@ cdecl _wcserror_s(ptr long long) MSVCRT__wcserror_s
@ cdecl _wcsftime_l(ptr long wstr ptr ptr) MSVCRT__wcsftime_l
@ cdecl _wcsicmp(wstr wstr) MSVCRT__wcsicmp
@ cdecl _wcsicmp_l(wstr wstr ptr) MSVCRT__wcsicmp_l
@ cdecl _wcsicoll(wstr wstr) MSVCRT__wcsicoll
@ cdecl _wcsicoll_l(wstr wstr ptr) MSVCRT__wcsicoll_l
@ cdecl _wcslwr(wstr) MSVCRT__wcslwr
@ cdecl _wcslwr_l(wstr ptr) MSVCRT__wcslwr_l
@ cdecl _wcslwr_s(wstr long) MSVCRT__wcslwr_s
@ cdecl _wcslwr_s_l(wstr long ptr) MSVCRT__wcslwr_s_l
@ cdecl _wcsncoll(wstr wstr long) MSVCRT__wcsncoll
@ cdecl _wcsncoll_l(wstr wstr long ptr) MSVCRT__wcsncoll_l
@ cdecl _wcsnicmp(wstr wstr long) MSVCRT__wcsnicmp
@ cdecl _wcsnicmp_l(wstr wstr long ptr) MSVCRT__wcsnicmp_l
@ cdecl _wcsnicoll(wstr wstr long) MSVCRT__wcsnicoll
@ cdecl _wcsnicoll_l(wstr wstr long ptr) MSVCRT__wcsnicoll_l
@ cdecl _wcsnset(wstr long long) MSVCRT__wcsnset
@ stub _wcsnset_s
@ cdecl _wcsrev(wstr) MSVCRT__wcsrev
@ cdecl _wcsset(wstr long) MSVCRT__wcsset
@ cdecl _wcsset_s(wstr long long) MSVCRT__wcsset_s
@ cdecl _wcstod_l(wstr ptr) MSVCRT__wcstod_l
@ cdecl -ret64 _wcstoi64(wstr ptr long) MSVCRT__wcstoi64
@ cdecl -ret64 _wcstoi64_l(wstr ptr long ptr) MSVCRT__wcstoi64_l
@ cdecl _wcstol_l(wstr ptr long ptr) MSVCRT__wcstol_l
@ cdecl _wcstombs_l(ptr ptr long ptr) MSVCRT__wcstombs_l
@ cdecl _wcstombs_s_l(ptr ptr long wstr long ptr) MSVCRT__wcstombs_s_l
@ cdecl -ret64 _wcstoui64(wstr ptr long) MSVCRT__wcstoui64
@ cdecl -ret64 _wcstoui64_l(wstr ptr long ptr) MSVCRT__wcstoui64_l
@ cdecl _wcstoul_l(wstr ptr long ptr) MSVCRT__wcstoul_l
@ cdecl _wcsupr(wstr) ntdll._wcsupr
@ cdecl _wcsupr_l(wstr ptr) MSVCRT__wcsupr_l
@ cdecl _wcsupr_s(wstr long) MSVCRT__wcsupr_s
@ cdecl _wcsupr_s_l(wstr long ptr) MSVCRT__wcsupr_s_l
@ cdecl _wcsxfrm_l(ptr wstr long ptr) MSVCRT__wcsxfrm_l
@ cdecl _wctime32(ptr) MSVCRT__wctime32
@ cdecl _wctime32_s(ptr long ptr) MSVCRT__wctime32_s
@ cdecl _wctime64(ptr) MSVCRT__wctime64
@ cdecl _wctime64_s(ptr long ptr) MSVCRT__wctime64_s
@ cdecl _wctomb_l(ptr long ptr) MSVCRT__wctomb_l
@ cdecl _wctomb_s_l(ptr ptr long long ptr) MSVCRT__wctomb_s_l
# extern _wctype
@ cdecl _wdupenv_s(ptr ptr wstr)
#@ extern _wenviron MSVCRT__wenviron
#@ varargs _wexecl(wstr wstr)
#@ varargs _wexecle(wstr wstr)
#@ varargs _wexeclp(wstr wstr)
#@ varargs _wexeclpe(wstr wstr)
@ cdecl _wexecv(wstr ptr)
@ cdecl _wexecve(wstr ptr ptr)
@ cdecl _wexecvp(wstr ptr)
@ cdecl _wexecvpe(wstr ptr ptr)
@ cdecl _wfdopen(long wstr) MSVCRT__wfdopen
@ cdecl _wfindfirst32(wstr ptr) MSVCRT__wfindfirst32
@ stub _wfindfirst32i64
@ cdecl _wfindfirst64(wstr ptr) MSVCRT__wfindfirst64
@ cdecl _wfindfirst64i32(wstr ptr) MSVCRT__wfindfirst64i32
@ cdecl _wfindnext32(long ptr) MSVCRT__wfindnext32
@ stub _wfindnext32i64
@ cdecl _wfindnext64(long ptr) MSVCRT__wfindnext64
@ cdecl _wfindnext64i32(long ptr) MSVCRT__wfindnext64i32
@ cdecl _wfopen(wstr wstr) MSVCRT__wfopen
@ cdecl _wfopen_s(ptr wstr wstr) MSVCRT__wfopen_s
@ cdecl _wfreopen(wstr wstr ptr) MSVCRT__wfreopen
@ cdecl _wfreopen_s(ptr wstr wstr ptr) MSVCRT__wfreopen_s
@ cdecl _wfsopen(wstr wstr long) MSVCRT__wfsopen
@ cdecl _wfullpath(ptr wstr long) MSVCRT__wfullpath
@ cdecl _wgetcwd(wstr long) MSVCRT__wgetcwd
@ cdecl _wgetdcwd(long wstr long) MSVCRT__wgetdcwd
@ stub _wgetdcwd_nolock
@ cdecl _wgetenv(wstr) MSVCRT__wgetenv
@ cdecl _wgetenv_s(ptr ptr long wstr)
@ cdecl _wmakepath(ptr wstr wstr wstr wstr) MSVCRT__wmakepath
@ cdecl _wmakepath_s(ptr long wstr wstr wstr wstr) MSVCRT__wmakepath_s
@ cdecl _wmkdir(wstr) MSVCRT__wmkdir
@ cdecl _wmktemp(wstr) MSVCRT__wmktemp
@ cdecl _wmktemp_s(wstr long) MSVCRT__wmktemp_s
#@ varargs _wopen(wstr long) MSVCRT__wopen
@ cdecl _wperror(wstr) MSVCRT__wperror
#@ extern _wpgmptr MSVCRT__wpgmptr
@ cdecl _wpopen(wstr wstr) MSVCRT__wpopen
@ stub _wprintf_l
@ stub _wprintf_p
@ stub _wprintf_p_l
@ stub _wprintf_s_l
@ cdecl _wputenv(wstr) MSVCRT__wputenv
@ cdecl _wputenv_s(wstr wstr)
@ cdecl _wremove(wstr) MSVCRT__wremove
@ cdecl _wrename(wstr wstr) MSVCRT__wrename
@ cdecl _write(long ptr long) MSVCRT__write
@ cdecl _wrmdir(wstr) MSVCRT__wrmdir
#@ varargs _wscanf_l(wstr ptr) MSVCRT__wscanf_l
#@ varargs _wscanf_s_l(wstr ptr) MSVCRT__wscanf_s_l
@ cdecl _wsearchenv(wstr wstr ptr) MSVCRT__wsearchenv
@ cdecl _wsearchenv_s(wstr wstr ptr long) MSVCRT__wsearchenv_s
@ cdecl _wsetlocale(long wstr) MSVCRT__wsetlocale
#@ varargs _wsopen(wstr long long) MSVCRT__wsopen
@ cdecl _wsopen_s(ptr wstr long long long) MSVCRT__wsopen_s
#@ varargs _wspawnl(long wstr wstr)
#@ varargs _wspawnle(long wstr wstr)
#@ varargs _wspawnlp(long wstr wstr)
#@ varargs _wspawnlpe(long wstr wstr)
@ cdecl _wspawnv(long wstr ptr) MSVCRT__wspawnv
@ cdecl _wspawnve(long wstr ptr ptr) MSVCRT__wspawnve
@ cdecl _wspawnvp(long wstr ptr) MSVCRT__wspawnvp
@ cdecl _wspawnvpe(long wstr ptr ptr) MSVCRT__wspawnvpe
@ cdecl _wsplitpath(wstr ptr ptr ptr ptr) MSVCRT__wsplitpath
@ cdecl _wsplitpath_s(wstr ptr long ptr long ptr long ptr long) MSVCRT__wsplitpath_s
@ cdecl _wstat32(wstr ptr) MSVCRT__wstat32
@ cdecl _wstat32i64(wstr ptr) MSVCRT__wstat32i64
@ cdecl _wstat64(wstr ptr) MSVCRT__wstat64
@ cdecl _wstat64i32(wstr ptr) MSVCRT__wstat64i32
@ cdecl _wstrdate(ptr) MSVCRT__wstrdate
@ cdecl _wstrdate_s(ptr long)
@ cdecl _wstrtime(ptr) MSVCRT__wstrtime
@ cdecl _wstrtime_s(ptr long)
@ cdecl _wsystem(wstr) MSVCRT__wsystem
@ cdecl _wtempnam(wstr wstr) MSVCRT__wtempnam
@ cdecl _wtmpnam(ptr) MSVCRT__wtmpnam
@ cdecl _wtmpnam_s(ptr long) MSVCRT__wtmpnam_s
@ cdecl _wtof(wstr) MSVCRT__wtof
@ cdecl _wtof_l(wstr ptr) MSVCRT__wtof_l
@ cdecl _wtoi(wstr) MSVCRT__wtoi
@ cdecl -ret64 _wtoi64(wstr) MSVCRT__wtoi64
@ cdecl -ret64 _wtoi64_l(wstr ptr) MSVCRT__wtoi64_l
@ cdecl _wtoi_l(wstr ptr) MSVCRT__wtoi_l
@ cdecl _wtol(wstr) MSVCRT__wtol
@ cdecl _wtol_l(wstr ptr) MSVCRT__wtol_l
@ cdecl _wunlink(wstr) MSVCRT__wunlink
@ cdecl _wutime32(wstr ptr) MSVCRT__wutime32
@ cdecl _wutime64(wstr ptr) MSVCRT__wutime64
@ cdecl _y0(double) MSVCRT__y0
@ cdecl _y1(double) MSVCRT__y1
@ cdecl _yn(long double) MSVCRT__yn
@ cdecl abort() MSVCRT_abort
@ cdecl abs(long) MSVCRT_abs
@ cdecl acos(double) MSVCRT_acos
@ cdecl -arch=arm,x86_64,arm64 acosf(float) MSVCRT_acosf
@ cdecl asctime(ptr) MSVCRT_asctime
@ cdecl asctime_s(ptr long ptr) MSVCRT_asctime_s
@ cdecl asin(double) MSVCRT_asin
@ cdecl -arch=arm,x86_64,arm64 asinf(float) MSVCRT_asinf
@ cdecl atan(double) MSVCRT_atan
@ cdecl -arch=arm,x86_64,arm64 atanf(float) MSVCRT_atanf
@ cdecl atan2(double double) MSVCRT_atan2
@ cdecl -arch=arm,x86_64,arm64 atan2f(float float) MSVCRT_atan2f
#@ cdecl -private atexit(ptr) MSVCRT_atexit  # not imported to avoid conflicts with Mingw
@ cdecl atof(str) MSVCRT_atof
@ cdecl atoi(str) MSVCRT_atoi
@ cdecl atol(str) ntdll.atol
@ cdecl bsearch(ptr ptr long long ptr) MSVCRT_bsearch
#@ cdecl bsearch_s(ptr ptr long long ptr ptr) MSVCRT_bsearch_s
@ cdecl btowc(long) MSVCRT_btowc
@ cdecl calloc(long long) MSVCRT_calloc
@ cdecl ceil(double) MSVCRT_ceil
@ cdecl -arch=arm,x86_64,arm64 ceilf(float) MSVCRT_ceilf
@ cdecl clearerr(ptr) MSVCRT_clearerr
#@ cdecl clearerr_s(ptr) MSVCRT_clearerr_s
@ cdecl clock() MSVCRT_clock
@ cdecl cos(double) MSVCRT_cos
@ cdecl -arch=arm,x86_64,arm64 cosf(float) MSVCRT_cosf
@ cdecl cosh(double) MSVCRT_cosh
@ cdecl -arch=arm,x86_64,arm64 coshf(float) MSVCRT_coshf
@ cdecl -ret64 div(long long) MSVCRT_div
@ cdecl exit(long) MSVCRT_exit
@ cdecl exp(double) MSVCRT_exp
@ cdecl -arch=arm,x86_64,arm64 expf(float) MSVCRT_expf
@ cdecl fabs(double) MSVCRT_fabs
@ cdecl fclose(ptr) MSVCRT_fclose
@ cdecl feof(ptr) MSVCRT_feof
@ cdecl ferror(ptr) MSVCRT_ferror
@ cdecl fflush(ptr) MSVCRT_fflush
@ cdecl fgetc(ptr) MSVCRT_fgetc
@ cdecl fgetpos(ptr ptr) MSVCRT_fgetpos
@ cdecl fgets(ptr long ptr) MSVCRT_fgets
@ cdecl fgetwc(ptr) MSVCRT_fgetwc
@ cdecl fgetws(ptr long ptr) MSVCRT_fgetws
@ cdecl floor(double) MSVCRT_floor
@ cdecl -arch=arm,x86_64,arm64 floorf(float) MSVCRT_floorf
@ cdecl fmod(double double) MSVCRT_fmod
@ cdecl -arch=arm,x86_64,arm64 fmodf(float float) MSVCRT_fmodf
@ cdecl fopen(str str) MSVCRT_fopen
@ cdecl fopen_s(ptr str str) MSVCRT_fopen_s
@ varargs fprintf(ptr str) MSVCRT_fprintf
#@ varargs fprintf_s(ptr str) MSVCRT_fprintf_s
@ cdecl fputc(long ptr) MSVCRT_fputc
@ cdecl fputs(str ptr) MSVCRT_fputs
@ cdecl fputwc(long ptr) MSVCRT_fputwc
@ cdecl fputws(wstr ptr) MSVCRT_fputws
@ cdecl fread(ptr long long ptr) MSVCRT_fread
@ cdecl fread_s(ptr long long long ptr) MSVCRT_fread_s
@ cdecl free(ptr) MSVCRT_free
@ cdecl freopen(str str ptr) MSVCRT_freopen
@ cdecl freopen_s(ptr str str ptr) MSVCRT_freopen_s
@ cdecl frexp(double ptr) MSVCRT_frexp
@ varargs fscanf(ptr str) MSVCRT_fscanf
#@ varargs fscanf_s(ptr str) MSVCRT_fscanf_s
@ cdecl fseek(ptr long long) MSVCRT_fseek
@ cdecl fsetpos(ptr ptr) MSVCRT_fsetpos
@ cdecl ftell(ptr) MSVCRT_ftell
@ varargs fwprintf(ptr wstr) MSVCRT_fwprintf
#@ varargs fwprintf_s(ptr wstr) MSVCRT_fwprintf_s
@ cdecl fwrite(ptr long long ptr) MSVCRT_fwrite
#@ varargs fwscanf(ptr wstr) MSVCRT_fwscanf
#@ varargs fwscanf_s(ptr wstr) MSVCRT_fwscanf_s
@ cdecl getc(ptr) MSVCRT_getc
@ cdecl getchar() MSVCRT_getchar
@ cdecl getenv(str) MSVCRT_getenv
@ cdecl getenv_s(ptr ptr long str)
@ cdecl gets(str) MSVCRT_gets
@ stub gets_s
@ cdecl getwc(ptr) MSVCRT_getwc
@ cdecl getwchar() MSVCRT_getwchar
@ cdecl is_wctype(long long) ntdll.iswctype
@ cdecl isalnum(long) MSVCRT_isalnum
@ cdecl isalpha(long) MSVCRT_isalpha
@ cdecl iscntrl(long) MSVCRT_iscntrl
@ cdecl isdigit(long) MSVCRT_isdigit
@ cdecl isgraph(long) MSVCRT_isgraph
@ cdecl isleadbyte(long) MSVCRT_isleadbyte
@ cdecl islower(long) MSVCRT_islower
@ cdecl isprint(long) MSVCRT_isprint
@ cdecl ispunct(long) MSVCRT_ispunct
@ cdecl isspace(long) MSVCRT_isspace
@ cdecl isupper(long) MSVCRT_isupper
@ cdecl iswalnum(long) MSVCRT_iswalnum
@ cdecl iswalpha(long) ntdll.iswalpha
@ cdecl iswascii(long) MSVCRT_iswascii
@ cdecl iswcntrl(long) MSVCRT_iswcntrl
@ cdecl iswctype(long long) ntdll.iswctype
@ cdecl iswdigit(long) MSVCRT_iswdigit
@ cdecl iswgraph(long) MSVCRT_iswgraph
@ cdecl iswlower(long) MSVCRT_iswlower
@ cdecl iswprint(long) MSVCRT_iswprint
@ cdecl iswpunct(long) MSVCRT_iswpunct
@ cdecl iswspace(long) MSVCRT_iswspace
@ cdecl iswupper(long) MSVCRT_iswupper
@ cdecl iswxdigit(long) MSVCRT_iswxdigit
@ cdecl isxdigit(long) MSVCRT_isxdigit
@ cdecl labs(long) MSVCRT_labs
@ cdecl ldexp(double long) MSVCRT_ldexp
@ cdecl ldiv(long long) MSVCRT_ldiv
@ cdecl -ret64 llabs(int64) MSVCRT_llabs
#@ cdecl lldiv(int64 int64) MSVCRT_lldiv
@ cdecl localeconv() MSVCRT_localeconv
@ cdecl log(double) MSVCRT_log
@ cdecl -arch=arm,x86_64,arm64 logf(float) MSVCRT_logf
@ cdecl log10(double) MSVCRT_log10
@ cdecl -arch=arm,x86_64,arm64 log10f(float) MSVCRT_log10f
@ cdecl -arch=i386,x86_64,arm,arm64 longjmp(ptr long) MSVCRT_longjmp
@ cdecl malloc(long) MSVCRT_malloc
@ cdecl mblen(ptr long) MSVCRT_mblen
@ cdecl mbrlen(ptr long ptr) MSVCRT_mbrlen
@ cdecl mbrtowc(ptr str long ptr) MSVCRT_mbrtowc
@ cdecl mbsrtowcs(ptr ptr long ptr) MSVCRT_mbsrtowcs
@ cdecl mbsrtowcs_s(ptr ptr long ptr long ptr) MSVCRT_mbsrtowcs_s
@ cdecl mbstowcs(ptr str long) MSVCRT_mbstowcs
@ cdecl mbstowcs_s(ptr ptr long str long) MSVCRT__mbstowcs_s
@ cdecl mbtowc(ptr str long) MSVCRT_mbtowc
@ cdecl memchr(ptr long long) MSVCRT_memchr
@ cdecl memcmp(ptr ptr long) MSVCRT_memcmp
@ cdecl memcpy(ptr ptr long) MSVCRT_memcpy
@ cdecl memcpy_s(ptr long ptr long) MSVCRT_memcpy_s
@ cdecl memmove(ptr ptr long) MSVCRT_memmove
@ cdecl memmove_s(ptr long ptr long) MSVCRT_memmove_s
@ cdecl memset(ptr long long) MSVCRT_memset
@ cdecl modf(double ptr) MSVCRT_modf
@ cdecl -arch=arm,x86_64,arm64 modff(float ptr) MSVCRT_modff
@ cdecl perror(str) MSVCRT_perror
@ cdecl pow(double double) MSVCRT_pow
@ cdecl -arch=arm,x86_64,arm64 powf(float float) MSVCRT_powf
@ varargs printf(str) MSVCRT_printf
#@ varargs printf_s(str) MSVCRT_printf_s
@ cdecl putc(long ptr) MSVCRT_putc
@ cdecl putchar(long) MSVCRT_putchar
@ cdecl puts(str) MSVCRT_puts
@ cdecl putwc(long ptr) MSVCRT_fputwc
@ cdecl putwchar(long) MSVCRT__fputwchar
@ cdecl qsort(ptr long long ptr) MSVCRT_qsort
#@ cdecl qsort_s(ptr long long ptr ptr) MSVCRT_qsort_s
@ cdecl raise(long) MSVCRT_raise
@ cdecl rand() MSVCRT_rand
#@ cdecl rand_s(ptr) MSVCRT_rand_s
@ cdecl realloc(ptr long) MSVCRT_realloc
@ cdecl remove(str) MSVCRT_remove
@ cdecl rename(str str) MSVCRT_rename
@ cdecl rewind(ptr) MSVCRT_rewind
#@ varargs scanf(str) MSVCRT_scanf
#@ varargs scanf_s(str) MSVCRT_scanf_s
@ cdecl setbuf(ptr ptr) MSVCRT_setbuf
@ cdecl -arch=arm,x86_64 -norelay -private setjmp(ptr) MSVCRT__setjmp
@ cdecl setlocale(long str) MSVCRT_setlocale
@ cdecl setvbuf(ptr str long long) MSVCRT_setvbuf
@ cdecl signal(long long) MSVCRT_signal
@ cdecl sin(double) MSVCRT_sin
@ cdecl -arch=arm,x86_64,arm64 sinf(float) MSVCRT_sinf
@ cdecl sinh(double) MSVCRT_sinh
@ cdecl -arch=arm,x86_64,arm64 sinhf(float) MSVCRT_sinhf
@ varargs sprintf(ptr str) MSVCRT_sprintf
@ varargs sprintf_s(ptr long str) MSVCRT_sprintf_s
@ cdecl sqrt(double) MSVCRT_sqrt
@ cdecl -arch=arm,x86_64,arm64 sqrtf(float) MSVCRT_sqrtf
@ cdecl srand(long) MSVCRT_srand
@ varargs sscanf(str str) MSVCRT_sscanf
@ varargs sscanf_s(str str) MSVCRT_sscanf_s
@ cdecl strcat(str str) ntdll.strcat
@ cdecl strcat_s(str long str) MSVCRT_strcat_s
@ cdecl strchr(str long) MSVCRT_strchr
@ cdecl strcmp(str str) MSVCRT_strcmp
@ cdecl strcoll(str str) MSVCRT_strcoll
@ cdecl strcpy(ptr str) MSVCRT_strcpy
@ cdecl strcpy_s(ptr long str) MSVCRT_strcpy_s
@ cdecl strcspn(str str) ntdll.strcspn
@ cdecl strerror(long) MSVCRT_strerror
@ cdecl strerror_s(ptr long long) MSVCRT_strerror_s
@ cdecl strftime(ptr long str ptr) MSVCRT_strftime
@ cdecl strlen(str) MSVCRT_strlen
@ cdecl strncat(str str long) MSVCRT_strncat
@ cdecl strncat_s(str long str long) MSVCRT_strncat_s
@ cdecl strncmp(str str long) MSVCRT_strncmp
@ cdecl strncpy(ptr str long) MSVCRT_strncpy
@ cdecl strncpy_s(ptr long str long) MSVCRT_strncpy_s
@ cdecl strnlen(str long) MSVCRT_strnlen
@ cdecl strpbrk(str str) ntdll.strpbrk
@ cdecl strrchr(str long) MSVCRT_strrchr
@ cdecl strspn(str str) ntdll.strspn
@ cdecl strstr(str str) MSVCRT_strstr
@ cdecl strtod(str ptr) MSVCRT_strtod
@ cdecl strtok(str str) MSVCRT_strtok
@ cdecl strtok_s(ptr str ptr) MSVCRT_strtok_s
@ cdecl strtol(str ptr long) MSVCRT_strtol
@ cdecl strtoul(str ptr long) MSVCRT_strtoul
@ cdecl strxfrm(ptr str long) MSVCRT_strxfrm
@ varargs swprintf_s(ptr long wstr) MSVCRT_swprintf_s
#@ varargs swscanf(wstr wstr) MSVCRT_swscanf
@ varargs swscanf_s(wstr wstr) MSVCRT_swscanf_s
@ cdecl system(str) MSVCRT_system
@ cdecl tan(double) MSVCRT_tan
@ cdecl -arch=arm,x86_64,arm64 tanf(float) MSVCRT_tanf
@ cdecl tanh(double) MSVCRT_tanh
@ cdecl -arch=arm,x86_64,arm64 tanhf(float) MSVCRT_tanhf
@ cdecl tmpfile() MSVCRT_tmpfile
@ cdecl tmpfile_s(ptr) MSVCRT_tmpfile_s
@ cdecl tmpnam(ptr) MSVCRT_tmpnam
@ cdecl tmpnam_s(ptr long) MSVCRT_tmpnam_s
@ cdecl tolower(long) MSVCRT_tolower
@ cdecl toupper(long) MSVCRT_toupper
@ cdecl towlower(long) MSVCRT_towlower
@ cdecl towupper(long) MSVCRT_towupper
@ cdecl ungetc(long ptr) MSVCRT_ungetc
@ cdecl ungetwc(long ptr) MSVCRT_ungetwc
@ cdecl vfprintf(ptr str ptr) MSVCRT_vfprintf
#@ cdecl vfprintf_s(ptr str ptr) MSVCRT_vfprintf_s
@ cdecl vfwprintf(ptr wstr ptr) MSVCRT_vfwprintf
#@ cdecl vfwprintf_s(ptr wstr ptr) MSVCRT_vfwprintf_s
@ cdecl vprintf(str ptr) MSVCRT_vprintf
#@ cdecl vprintf_s(str ptr) MSVCRT_vprintf_s
@ cdecl vsprintf(ptr str ptr) MSVCRT_vsprintf
@ cdecl vsprintf_s(ptr long str ptr) MSVCRT_vsprintf_s
@ cdecl vswprintf_s(ptr long wstr ptr) MSVCRT_vswprintf_s
#@ cdecl vwprintf(wstr ptr) MSVCRT_vwprintf
#@ cdecl vwprintf_s(wstr ptr) MSVCRT_vwprintf_s
#@ cdecl wcrtomb(ptr long ptr) MSVCRT_wcrtomb
@ stub wcrtomb_s
@ cdecl wcscat(wstr wstr) ntdll.wcscat
@ cdecl wcscat_s(wstr long wstr) MSVCRT_wcscat_s
@ cdecl wcschr(wstr long) MSVCRT_wcschr
@ cdecl wcscmp(wstr wstr) ntdll.wcscmp
@ cdecl wcscoll(wstr wstr) MSVCRT_wcscoll
@ cdecl wcscpy(ptr wstr) ntdll.wcscpy
@ cdecl wcscpy_s(ptr long wstr) MSVCRT_wcscpy_s
@ cdecl wcscspn(wstr wstr) ntdll.wcscspn
@ cdecl wcsftime(ptr long wstr ptr) MSVCRT_wcsftime
@ cdecl wcslen(wstr) MSVCRT_wcslen
@ cdecl wcsncat(wstr wstr long) ntdll.wcsncat
@ cdecl wcsncat_s(wstr long wstr long) MSVCRT_wcsncat_s
@ cdecl wcsncmp(wstr wstr long) MSVCRT_wcsncmp
@ cdecl wcsncpy(ptr wstr long) MSVCRT_wcsncpy
@ cdecl wcsncpy_s(ptr long wstr long) MSVCRT_wcsncpy_s
@ cdecl wcsnlen(wstr long) MSVCRT_wcsnlen
@ cdecl wcspbrk(wstr wstr) MSVCRT_wcspbrk
@ cdecl wcsrchr(wstr long) ntdll.wcsrchr
@ cdecl wcsrtombs(ptr ptr long ptr) MSVCRT_wcsrtombs
@ cdecl wcsrtombs_s(ptr ptr long ptr long ptr) MSVCRT_wcsrtombs_s
@ cdecl wcsspn(wstr wstr) ntdll.wcsspn
@ cdecl wcsstr(wstr wstr) MSVCRT_wcsstr
@ cdecl wcstod(wstr ptr) MSVCRT_wcstod
@ cdecl wcstok(wstr wstr) MSVCRT_wcstok
@ cdecl wcstok_s(ptr wstr ptr) MSVCRT_wcstok_s
@ cdecl wcstol(wstr ptr long) ntdll.wcstol
@ cdecl wcstombs(ptr ptr long) MSVCRT_wcstombs
@ cdecl wcstombs_s(ptr ptr long wstr long) MSVCRT_wcstombs_s
@ cdecl wcstoul(wstr ptr long) MSVCRT_wcstoul
@ cdecl wcsxfrm(ptr wstr long) MSVCRT_wcsxfrm
@ cdecl wctob(long) MSVCRT_wctob
@ cdecl wctomb(ptr long) MSVCRT_wctomb
@ cdecl wctomb_s(ptr ptr long long) MSVCRT_wctomb_s
@ cdecl wmemcpy_s(ptr long ptr long)
@ cdecl wmemmove_s(ptr long ptr long)
@ varargs wprintf(wstr) MSVCRT_wprintf
#@ varargs wprintf_s(wstr) MSVCRT_wprintf_s
#@ varargs wscanf(wstr) MSVCRT_wscanf
#@ varargs wscanf_s(wstr) MSVCRT_wscanf_s
