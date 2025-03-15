#pragma once

#include <vector>
#include <shared_mutex>
#include ".\SimpleIni\SimpleIni.h"

//Abstraction - i.e. 'KeySettings' hides details of managing keys settings
class KeySettings
{
public:
	class KeyEntry
	{
	public:
		// Overloaded constructor
		KeyEntry(){}
		KeyEntry(uint8_t vKeyCode)
		{
			Init(vKeyCode);
		}

		uint8_t keyCode = 0;
		std::string name;
		std::string keyCodeStr;
		bool bExtended = false;

	protected:
		// Polymorphism / function overloading
		// Updates strings for GUI
		void Init();
		void Init(uint8_t vKeyCode);
		//

		bool bMacroValid = false;
		bool bPlaybackValid = false;
		
		// Only allow  protected members to be accessed by this class & and sub-classes
		friend class KeySettings;
	};

	class PlaybackKey : public KeyEntry // Inheritance
	{
	public:
		PlaybackKey() {}
		PlaybackKey(uint8_t vKeyCode, uint16_t _delayInMS)
		{
			keyCode = vKeyCode;
			delayInMS = _delayInMS;
			Init();
		}

		bool bShift = false;
		bool bCtrl  = false;
		bool bAlt   = false;
		bool bWKey  = false;
		uint16_t    delayInMS = 0;
		std::string delayInMSStr;

	protected:
		// Function Overriding
		// Updates strings for GUI
		void Init()
		{
			delayInMSStr = std::to_string(delayInMS);
			KeyEntry::Init(keyCode);
		}
		//

		// Only allow  protected members to be accessed by this class & and sub-classes
		friend class KeySettings;
	};

	class MacroKey : public KeyEntry
	{
	public:
		MacroKey() {}
		MacroKey(uint8_t vKeyCode)
		{
			KeyEntry::Init(vKeyCode);
		}

		bool bLoop = false;
		std::vector<PlaybackKey> keys;
	};

public: 
	// Loads key settings from file
	bool Init(WCHAR* fileName); //file name only (i.e. no path)
		
	// Macro APIs
	bool Macro_ListAvailable(std::vector<KeyEntry>& keys, uint8_t currentKeyCode); // Returns keys that can be  used as macro keys
	bool Macro_ListActive(std::vector<KeyEntry>& list); // Returns all active macros
	bool Macro_Add(MacroKey& macroKey);
	bool Macro_Delete(uint8_t keyCode);
	bool Macro_IsActive(uint8_t keyCode);
	bool Macro_Get(uint8_t keyCode, MacroKey& macroKey);

	// Playback key APIs
	bool Playback_ListAvailable(std::vector<KeyEntry>& keys); // Returns keys that can be used as a playback keys
	bool Playback_Get(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey);
	bool Playback_Add(uint8_t macroKeyCode, int playbackIdx, PlaybackKey& playbackKey);
	bool Playback_Delete(uint8_t macroKeyCode, int playbackIdx);
	
private:
	// Parse Ini file
	bool Ini_Parse(CSimpleIniA& m_ini);
	bool Ini_ParseSection(CSimpleIniA& m_ini, MacroKey& key, const char* sectionName);
	std::vector<std::string> Split(const char* str, char delimiter);

	// Misc
	bool GetMacro(uint8_t keyCode, MacroKey& macroKey);

private:
	CSimpleIniA m_ini;
	WCHAR m_fullPathToFile[MAX_PATH] = { 0 };
	std::map<uint8_t, MacroKey> m_macroKeys;

	// Can't use std::mutex because I'm compiling with /clr option.
	// https://developercommunity.visualstudio.com/t/shared-mutex-and-clr/469913
	std::shared_mutex protectSettings;

	uint8_t m_macroIsActive[256] = { 0 };
	const uint8_t maxKeysAllowed = 30;
};

extern KeySettings globalSettings;