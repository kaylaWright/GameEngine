#ifndef GAMEENGINE_H
#define GAMEENGINE_H
// Macro for deleting pointers - ensure memory cleanup
#define SAFE_DELETE(p) { if (p) { delete(p); p = NULL; } }
#include <Windows.h>
#include <WindowsX.h>
#include <LuaPlus.h>

#include "Audio\AudioManager.h"
#include "ECS\ECSManager.h"
#include "Graphics\GraphicsManager.h"
#include "Input\InputManager.h"
#include "ResourceLoader.h"
#include "Events\EventManager.h"
#include "DebugManager.h"
#include "Script\XMLScriptManager.h"
#include "Script\LuaScriptManager.h"
#include "Graphics\Camera.h"

// Removed, circular dependencies. Forward declared instead
// TODO find out if this is the proper solution to circular dependencies
//#include "GUI\GUIManager.h"
class GUIManager;
#include "Timer.h"

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	// Initialize engine classes and resources
	bool Init(HINSTANCE);
	// Initialize window with width height values
	bool InitializeWindows(int, int);
	// Update game world (based on frame time)
	bool Update();
	// handles the main loop of the engine.
	void Run();
	// Renders the next frame
	void RenderFrame();
	// Hault update calls by engine
	void Pause();
	// Called at termination, free memory, clear pointers, etc
	void Shutdown();
	// Shutdown calls specific to window(s)
	void ShutDownWindows();
	// System for passing calls to other classes
	LRESULT CALLBACK  MessageHandler(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam);
	// Used to determine time between frames
	void CalculateFPS();
	// A simple test of scripting system
	void ScriptTest();
	// Temporary function to set up the demo GUI
	bool BuildTestGUI();

	//get/sets.
	AudioManager* GetAudioManager()
	{ return audioManager; } 
	GraphicsManager* GetGraphicsManager()
	{ return graphicsManager; } 
	EventManager* GetEventManager()
	{ return eventManager; }
	InputManager* GetInputManager()
	{ return inputManager; }

private:
	LPCWSTR applicationName;
	HINSTANCE hInstance;
	HWND hWnd;
	
	AudioManager* audioManager;
	ECSManager* ecsManager;
	InputManager* inputManager;
	XMLScriptManager* xmlScriptManager;
	LuaScriptManager* luaScriptManager;
	EventManager* eventManager;
	DebugManager* debugManager;
	ResourceLoader* resourceLoader;
	GraphicsManager* graphicsManager;
	//GUIManager* guiManager;
	Camera* camera;

	Timer timer;

	float framesPerSecond;
};

// the WindowProc function prototype
static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static GameEngine* ApplicationHandle = NULL;

#endif