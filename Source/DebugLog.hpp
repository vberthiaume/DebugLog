#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define ENABLE_DEBUG_LOG 1

#if JUCE_WINDOWS
static const juce::File memoryMappedFile { "C:/temp/ProPhatSharedMemory" };
#else
static const juce::File memoryMappedFile { "/tmp/ProPhatSharedMemory" };
#endif

static constexpr auto kMaxDebugEntries { 2048 };

//======================================================================================
struct DebugLogEntry
{
    juce::int64 timeSinceLastCall {};
    juce::int64 processCallDuration {};
    int         curEffect {};
};

//======================================================================================
struct DebugLog
{
    DebugLogEntry   log[kMaxDebugEntries];
    volatile size_t logHead {};
};

//======================================================================================
inline void printDebugLogEntry (DebugLogEntry& logEntry)
{
    std::cout << "time since: " << juce::String (logEntry.timeSinceLastCall)
    << ", duration: " << juce::String (logEntry.processCallDuration)
    << ", Effect: " << logEntry.curEffect << std::endl;
}
