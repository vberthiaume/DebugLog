#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define ENABLE_DEBUG_LOG 0
#define ENABLE_GAIN_LOGGING ENABLE_DEBUG_LOG && 1

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
#if ENABLE_GAIN_LOGGING
    float firstGain {};
    float lastGain {};
#endif
};

//======================================================================================
struct DebugLog
{
    DebugLogEntry   log[kMaxDebugEntries];
    volatile size_t logHead {};
};

//======================================================================================
inline void printDebugLogEntry (size_t index, DebugLogEntry& logEntry)
{
    std::cout << index
//              << ": time since: " << juce::String (logEntry.timeSinceLastCall)
//              << ", duration: " << juce::String (logEntry.processCallDuration)
              << ", effect: " << logEntry.curEffect
#if ENABLE_GAIN_LOGGING
              << ", first gain: " << logEntry.firstGain
              << ", last gain: " << logEntry.lastGain
#endif
              << "\n";
}
