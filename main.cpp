#include <QApplication>
#include <QThread>
#include "todopool.h"
#include "utils.h"
#include "core.h"
#include <stdio.h>

int InitBackend()
{
    Core *core = new Core();
    return (0);
}

/* Called by the main loop */
int UpdateCore()
{
    printf("%s\n", "[MAIN_LOOP]");
    return (0);
}

int UpdateGui()
{
    return (0);
}

int main(int argc, char **argv)
{
    int i = InitBackend();
    /* will be threaded */
    while (1)
    {
        UpdateCore();
    }
    QCoreApplication app(argc, argv);
}
