// Copyright (C) 2021  Santiago Acquarone
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
