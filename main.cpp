#include <QApplication>
#include <QThread>
#include "utils.h"

int InitBackend()
{
    return (0);
}

int main(int argc, char **argv)
{
    int i = InitBackend();
    QCoreApplication app(argc, argv);
}
