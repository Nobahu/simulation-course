#ifndef MAGIC8BALL_H
#define MAGIC8BALL_H

#include <QMainWindow>
#include <QVector>
#include <QRandomGenerator>
#include <QTimer>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QLabel;
class QComboBox;
QT_END_NAMESPACE

class Magic8Ball : public QMainWindow
{
    Q_OBJECT

public:
    Magic8Ball(QWidget *parent = nullptr);
    ~Magic8Ball();

private slots:
    void onAskClicked();
    void onGameChanged(int index);

private:
    void setupUI();
    void initAnswers();
    QString getRandomAnswer();

    // UI элементы
    QLineEdit *questionEdit;
    QPushButton *askButton;
    QLabel *ballLabel;
    QLabel *answerLabel;
    QComboBox *gameCombo;

    // Данные
    QVector<QString> yesNoAnswers;
    QVector<QString> magic8Answers;
    int currentGame; // 0 - YES/NO, 1 - Magic 8 Ball
};

#endif // MAGIC8BALL_H
