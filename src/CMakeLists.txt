add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_org.kde.krunnercrypto\")

add_library(krunnercrypto MODULE)

target_sources(krunnercrypto PRIVATE
    krunnercrypto.cpp
    coingecko.cpp
)

kcoreaddons_desktop_to_json(krunnercrypto plasma-runner-krunnercrypto.desktop)
find_package(Qt5Network REQUIRED)
target_link_libraries(krunnercrypto KF5::Runner KF5::I18n Qt5::Network Qt5::Widgets)

install(TARGETS krunnercrypto DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/krunner)

install(FILES plasma-runner-krunnercrypto.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
