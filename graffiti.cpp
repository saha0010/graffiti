// Die Anwendungsklasse
#include "GraffitiEngine.h"

int main(int argv, char **argc)
{
    vlgGlutEngine *app = GraffitiEngine::Instance();
    app->initApplication(argv, argc, 400, 300, 900, 500); // 400x400 Fentergr��e, Posiotion 900,500
    app->run();
    return 0;
}