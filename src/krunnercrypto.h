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
