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
