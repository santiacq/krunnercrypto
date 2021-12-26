# krunnercrypto
A KRunner plugin to view the current price of cryptocurrencies.

It works using [CoinGecko API V3.](https://www.coingecko.com/en/api/documentation)

![krunnercrypto2](https://user-images.githubusercontent.com/7107694/146843950-ce2e7a43-e623-46aa-8627-9d56f13a92c1.png)

## Configuration
The configuration file is located in `~/.config/krunnercrypto/config.json`

There are two things that must be configured:

1. Cryptocurrencies that are of interest. Results will only be shown for these cryptocurrencies.

2. Currencies to convert the cryptocurrencies to. (vs_currencies)

The cryptocurrencies that are of interest must have an entry in `cryptocurrencies` as shown in the example. Where `coingecko_id` is the id of the cryptocurrency in the CoinGecko API, `name` is the name of the cryptocurrency, and `short` is the short name for it.

The `name` and `short` of an entry are the terms that the plugin will recognize.

The desiered vs_currencies must be included in `vs_currencies` as shown in the example. These can only be vs_currencies supported by CoinGecko API.

The following is the configuration which was used to create the screenshot above.
```json
{   "cryptocurrencies" : [
        { "coingecko_id" : "bitcoin", "name" : "bitcoin", "short" : "btc" },
        { "coingecko_id" : "ethereum", "name" : "ethereum", "short" : "eth" },
        { "coingecko_id" : "solana", "name" : "solana", "short" : "sol" },
        { "coingecko_id" : "nano", "name" : "nano", "short" : "nano" }
    ],
    "vs_currencies" : [ "usd", "eur", "btc", "gbp" ]
}
```

## Usage
Launch KRunner and type the `name` or `short` of one of the cryptocurrencies that have been configured. The runner will show the price of said cryptocurrency in the configured vs_currencies.

## Dependencies

Ubuntu/Debian:
`sudo apt install cmake extra-cmake-modules build-essential libkf5runner-dev gettext`

Arch/Manjaro:
`sudo pacman -S cmake extra-cmake-modules`

Fedora:
`sudo dnf install cmake extra-cmake-modules kf5-ki18n-devel kf5-krunner-devel gettext`

OpenSUSE:
`sudo zypper install cmake extra-cmake-modules libQt5Core5 libqt5-qtlocation-devel ki18n-devel krunner-devel gettext-tools`

## Installation
1. Install dependencies
2. Clone this repository
3. Run install.sh

## Credits/Thanks
- [naraesk/krunner-translator](https://github.com/naraesk/krunner-translator) this project was really useful as a reference about consuming a REST API with Qt libraries.
- [alex1701c/JetBrainsRunner](https://github.com/alex1701c/JetBrainsRunner) this project was useful as a reference about the dependencies needed to compile/install the plugin in different distributions.
