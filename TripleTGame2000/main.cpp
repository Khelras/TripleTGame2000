#include "cProjectManager.h"

int main()
{
    cProjectManager& ProjectManager = cProjectManager::GetInstance();
    ProjectManager.RunProgram();

    return 0;
}
