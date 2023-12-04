class MainMenuManager
{
private:
    static void ShowWindow();

    static void SetWidgets();

    static inline bool game_started = false;
public:
    MainMenuManager() = delete;

    static void StartMenu();
    static void EndMenu();

    static bool GameStarted();
};
