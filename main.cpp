#include "notepad.h"
#include <QApplication>
#include <QMouseEvent>
#include <QToolTip>
#include <QTextCursor>
#include <QPixmap>
#include <QTimer>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Notepad w;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    w.setMaximumSize(screenGeometry.size());
    w.resize(screenGeometry.size());
    // You can display any image like an introduction, just comment out the below part and add path.
    // QPixmap pixmap("C:/Users/HP/Downloads/resized-image-transformed.png");
    // QSplashScreen splash(pixmap);
    // // splash.resize(w.size());
    // splash.show();
    // QTimer::singleShot(5000, [&splash, &w]() {
    //     splash.close();
    //     w.show();
    // });
    w.show();
    return a.exec();
}
