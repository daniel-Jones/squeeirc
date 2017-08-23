#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QtNetwork/QTcpSocket>

class worker : public QObject
{
	Q_OBJECT
	public:
		explicit worker(QObject *parent = nullptr);

	signals:

		public slots:
};

class network : public QObject
{
	Q_OBJECT
	public:
		network(int, QString, int, QString);
		void sconnect();
		int id;
		QString server;
		int port;
		QString name;
		QList<QString> channels;
	private:
		QTcpSocket *socket;
		void parse(QString line); 
	signals:
		private slots:
			void read();
};


#endif // WORKER_H
