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

#include "coingecko.h"

#include <QtGlobal>
#include <QJsonArray>
#include <QJsonDocument>
#include <QUrlQuery>
#include <KLocalizedString>
#include <qstringliteral.h>
#include <QFile>
#include <qdir.h>

CoinGecko::CoinGecko(Plasma::AbstractRunner *runner, Plasma::RunnerContext &context)
    : m_runner(runner), m_context(context) {

    // Read configuration file
    QFile configFile(QDir::homePath() + QStringLiteral("/.config/krunnercrypto/config.json"));
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString jsonStringConfig = QStringLiteral("");
    QTextStream in(&configFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        jsonStringConfig.append(line);
    }

    const QJsonObject jsonObjectConfig = QJsonDocument::fromJson(jsonStringConfig.toUtf8()).object();
    QJsonArray cryptocurrencies = jsonObjectConfig.value(QStringLiteral("cryptocurrencies")).toArray();
    QJsonArray vs_currencies = jsonObjectConfig.value(QStringLiteral("vs_currencies")).toArray();

    // Generate querry based on the configuration
    QString cryptocurrenciesQuerry = QStringLiteral("");
    for (auto entry : cryptocurrencies) {
        QJsonObject entryObject = entry.toObject();
        if (cryptocurrenciesQuerry != QStringLiteral("")) {
             cryptocurrenciesQuerry.append(QStringLiteral(","));
         }
         cryptocurrenciesQuerry.append(entryObject.value(QStringLiteral("coingecko_id")).toVariant().toString());
    }

    QString vs_currenciesQuerry = QStringLiteral("");
    for (auto entry : vs_currencies) {
        QString entryString = entry.toVariant().toString();
        if (vs_currenciesQuerry != QStringLiteral("")) {
             vs_currenciesQuerry.append(QStringLiteral(","));
         }
         vs_currenciesQuerry.append(entryString);
    }

    // Make request to the API
    m_manager = new QNetworkAccessManager(this);

    QUrl apiUrl = QUrl(QStringLiteral("https://api.coingecko.com/api/v3/simple/price?ids=") + cryptocurrenciesQuerry + QStringLiteral("&vs_currencies=") + vs_currenciesQuerry);
    QNetworkRequest request(apiUrl);

    m_manager->get(request);
    connect(m_manager, &QNetworkAccessManager::finished, this, &CoinGecko::parseResult);
}

void CoinGecko::parseResult(QNetworkReply *reply) {
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) != 200) {
        Q_EMIT finished();
        return;
    }

    // Read configuration file
    QFile configFile(QDir::homePath() + QStringLiteral("/.config/krunnercrypto/config.json"));
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString jsonString = QStringLiteral("");
    QTextStream in(&configFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        jsonString.append(line);
    }

    const QJsonObject jsonObjectConfig = QJsonDocument::fromJson(jsonString.toUtf8()).object();
    QJsonArray cryptocurrencies = jsonObjectConfig.value(QStringLiteral("cryptocurrencies")).toArray();
    QJsonArray vs_currencies = jsonObjectConfig.value(QStringLiteral("vs_currencies")).toArray();

    const QString term = m_context.query();
    for (auto entry : cryptocurrencies) {
        // Case insensitive comparison with the short and long names of the cryptocurrencies to check for matches
        if (term.toUpper() == entry.toObject().value(QStringLiteral("name")).toVariant().toString().toUpper() ||
            term.toUpper() == entry.toObject().value(QStringLiteral("short")).toVariant().toString().toUpper()) {

            // jsonStringData is a string with the data as its given by the API
            const QString jsonStringData = QString::fromUtf8(reply->readAll());
            const QJsonObject jsonObjectData = QJsonDocument::fromJson(jsonStringData.toUtf8()).object();

            QList<Plasma::QueryMatch> matches;
            float relevance = 1;
            for (auto currency : vs_currencies) {
                Plasma::QueryMatch match(m_runner);
                QString cryptoId = entry.toObject().value(QStringLiteral("name")).toVariant().toString();
                QString currencyString = currency.toVariant().toString();
                const QString price = jsonObjectData.value(cryptoId).toObject().value(currencyString).toVariant().toString();
                QString shortString = entry.toObject().value(QStringLiteral("short")).toVariant().toString().toUpper();

                match.setText(i18n("1 %1 = %2 %3", shortString.toUpper(), price, currencyString.toUpper()));
                match.setIcon(QIcon::fromTheme(QStringLiteral("bitcoin")));
                match.setRelevance(relevance);
                matches.append(match);
                relevance -= 0.01;
            }
            m_context.addMatches(matches);

        }

    }

    Q_EMIT finished();
}

#include "moc_coingecko.cpp"
