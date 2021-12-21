#ifndef COINGECKO_H
#define COINGECKO_H

#include <KRunner/AbstractRunner>
#include <QtNetwork/QNetworkReply>

class CoinGecko : public QObject
{
    Q_OBJECT

public:
    CoinGecko(Plasma::AbstractRunner*, Plasma::RunnerContext&);

private Q_SLOTS:
   void parseResult(QNetworkReply*);

Q_SIGNALS:
	void finished();

private:
   Plasma::AbstractRunner * m_runner;
   QNetworkAccessManager * m_manager;
   Plasma::RunnerContext m_context;
};

#endif
