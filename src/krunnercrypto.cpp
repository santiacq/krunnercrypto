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

#include "krunnercrypto.h"

// KF
#include <KLocalizedString>

#include "coingecko.h"

krunnercrypto::krunnercrypto(QObject *parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    setObjectName(QStringLiteral("krunnercrypto"));
}

krunnercrypto::~krunnercrypto()
{
}


void krunnercrypto::match(Plasma::RunnerContext &context)
{
    QEventLoop loop;
    CoinGecko coingecko(this, context);
    connect(&coingecko, &CoinGecko::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

void krunnercrypto::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)
}

K_EXPORT_PLASMA_RUNNER_WITH_JSON(krunnercrypto, "plasma-runner-krunnercrypto.json")

// needed for the QObject subclass declared as part of K_EXPORT_PLASMA_RUNNER_WITH_JSON
#include "krunnercrypto.moc"
