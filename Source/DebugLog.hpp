#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define ENABLE_DEBUG_LOG 1
#define ENABLE_GAIN_LOGGING ENABLE_DEBUG_LOG && 0

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
    //this cannot be a string, it needs to be a fixed size char array, because the printing is based on size
    char gainRamp[5120]; //it takes 7 chars per float, so approximation here is 10x the buffer size i have lol
#endif
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
              << ", effect: " << logEntry.curEffect
#if ENABLE_GAIN_LOGGING
              << ", gainRamp: " << logEntry.gainRamp
#endif
              << "\n";
}
