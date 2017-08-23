#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include "worker.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	worker work;
	return a.exec();
}
