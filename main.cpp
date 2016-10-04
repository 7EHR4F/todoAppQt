#include <QApplication>
#include <QThread>
#include "todopool.h"
#include "utils.h"
#include "stdio.h"

int InitBackend()
{
    TodoPool *todopool = new TodoPool("CreatedAt", "Desc");
    return (0);
}

int UpdateCore()
{
    printf("%s\n", "[MAIN_LOOP]");
    return (0);
}

int main(int argc, char **argv)
{
    int i = InitBackend();
    while (1)
    {
        UpdateCore();
    }
    QCoreApplication app(argc, argv);
}
