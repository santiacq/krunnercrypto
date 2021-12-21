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

#ifndef KRUNNERCRYPTO_H
#define KRUNNERCRYPTO_H

#include <KRunner/AbstractRunner>

class krunnercrypto : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    krunnercrypto(QObject *parent, const QVariantList &args);
    ~krunnercrypto() override;

public: // Plasma::AbstractRunner API
    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;
};

#endif
