#ifndef HAVE_THUNK_EVNTRACE_H
#define HAVE_THUNK_EVNTRACE_H

struct qemu_EVENT_TRACE_PROPERTIES
{
    WNODE_HEADER Wnode;
    ULONG BufferSize;
    ULONG MinimumBuffers;
    ULONG MaximumBuffers;
    ULONG MaximumFileSize;
    ULONG LogFileMode;
    ULONG FlushTimer;
    ULONG EnableFlags;
    LONG AgeLimit;
    ULONG NumberOfBuffers;
    ULONG FreeBuffers;
    ULONG EventsLost;
    ULONG BuffersWritten;
    ULONG LogBuffersLost;
    ULONG RealTimeBuffersLost;
    qemu_ptr LoggerThreadId;
    ULONG LogFileNameOffset;
    ULONG LoggerNameOffset;
};

static inline void EVENT_TRACE_PROPERTIES_g2h(EVENT_TRACE_PROPERTIES *host, const struct qemu_EVENT_TRACE_PROPERTIES *guest)
{
    host->Wnode = guest->Wnode;
    host->BufferSize = guest->BufferSize;
    host->MinimumBuffers = guest->MinimumBuffers;
    host->MaximumBuffers = guest->MaximumBuffers;
    host->MaximumFileSize = guest->MaximumFileSize;
    host->LogFileMode = guest->LogFileMode;
    host->FlushTimer = guest->FlushTimer;
    host->EnableFlags = guest->EnableFlags;
    host->AgeLimit = guest->AgeLimit;
    host->NumberOfBuffers = guest->NumberOfBuffers;
    host->FreeBuffers = guest->FreeBuffers;
    host->EventsLost = guest->EventsLost;
    host->BuffersWritten = guest->BuffersWritten;
    host->LogBuffersLost = guest->LogBuffersLost;
    host->RealTimeBuffersLost = guest->RealTimeBuffersLost;
    host->LoggerThreadId = HANDLE_g2h(guest->LoggerThreadId);
    host->LogFileNameOffset = guest->LogFileNameOffset;
    host->LoggerNameOffset = guest->LoggerNameOffset;
}

static inline void EVENT_TRACE_PROPERTIES_h2g(struct qemu_EVENT_TRACE_PROPERTIES *guest, const EVENT_TRACE_PROPERTIES *host)
{
    guest->Wnode = host->Wnode;
    guest->BufferSize = host->BufferSize;
    guest->MinimumBuffers = host->MinimumBuffers;
    guest->MaximumBuffers = host->MaximumBuffers;
    guest->MaximumFileSize = host->MaximumFileSize;
    guest->LogFileMode = host->LogFileMode;
    guest->FlushTimer = host->FlushTimer;
    guest->EnableFlags = host->EnableFlags;
    guest->AgeLimit = host->AgeLimit;
    guest->NumberOfBuffers = host->NumberOfBuffers;
    guest->FreeBuffers = host->FreeBuffers;
    guest->EventsLost = host->EventsLost;
    guest->BuffersWritten = host->BuffersWritten;
    guest->LogBuffersLost = host->LogBuffersLost;
    guest->RealTimeBuffersLost = host->RealTimeBuffersLost;
    guest->LoggerThreadId = (ULONG_PTR)host->LoggerThreadId;
    guest->LogFileNameOffset = host->LogFileNameOffset;
    guest->LoggerNameOffset = host->LoggerNameOffset;
}

#endif
