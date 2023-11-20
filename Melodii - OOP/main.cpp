#include "MelodiiOOP.h"
#include <QtWidgets/QApplication>
#include "MelodieGUI.h"

int main(int argc, char *argv[])
{
    testDomain();
    testRepository();
    testService();

    QApplication a(argc, argv);
    RepoMelodie repo{ "melodii.txt" };
    ValidatorMelodie validator;
    ServiceMelodie srv{ repo, validator };
    MelodieGUI gui{ srv };
    gui.show();
    return a.exec();
}
