#include "worker.h"

worker::worker(QObject *parent) : QObject(parent)
{

	QList<network*> networks;
	network *net1 = new network(1, "irc.danieljon.es", 6667, "squeeirc1");
	networks.append(net1);
	net1->channels.append("#csgo");

	for (int i = 0; i < networks.count(); i++)
	{
		networks.at(i)->sconnect();
	}
}

network::network(int i, QString s, int p, QString n)
{
	id = i;
	server = s;
	port = p;
	name = n;
	socket = new QTcpSocket(this);
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}
void network::sconnect()
{
//	qDebug() << id << server << port;
	socket->connectToHost(server, port);
	QString nmsg = "NICK " + name + " \r\n";
	socket->write(nmsg.toLatin1());
	nmsg = "USER " + name + " 8 * :" + name + " \r\n";
	socket->write(nmsg.toLatin1());
}

void network::read()
{
	QString line = socket->readLine();
	if (line.contains("PING :"))
	{
			QString sline = "PONG :" + line.split(":")[1];
			socket->write(sline.toLatin1());
	}
	if (line.contains(name + " MODE " + name + " :+"))
	{
		for (int i = 0; i < channels.count(); i++)
		{
			QString d = "JOIN " + channels.at(i) + " \r\n";
			socket->write(d.toLatin1());
		}
	}
	if (line.contains("!"))
		parse(line);
	if(socket->canReadLine())
		read();

}

void network::parse(QString line)
{
	qDebug() << line;
}

