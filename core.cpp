#include "core.h"
#include "todopool.h"
#include "todo.h"

/* Constructs a Core object that will be used all along the app life-cycle */
Core::Core()
{
    Core::LoadAssets();
    TodoPool *todopool = new TodoPool("CreatedAt", "Desc");
}

/* this method will be used to load the graphical assets needed for the GUI */
int Core::LoadAssets()
{
    return(0);
}
