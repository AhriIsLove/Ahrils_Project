#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum KOREANSTATUS{
    CHO, //초성입력가능상태
    JONG,//종성입력가능상태
        //1.초성이입력된상태에서중성이입력된후
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //갱신
    void Update();

    //모음 조합
    QString CombineVowles(QString str);
    //글자 조합 알고리즘
    void CombineKoreanAlgorithm(QString *inputStr);

    //조합가능한 초성인지 확인(ㄲ,ㄸ,ㅃ,ㅆ,ㅉ)
    QString CombineChoSeung(QString cho1, QString cho2);
    //조합가능한 종성인지 확인(ㄲ,ㄳ,ㄵ,ㄶ,ㄺ,ㄻ,ㄼ,ㄽ,ㄾ,ㄿ,ㅀ,ㅄ,ㅆ)
    QString CombineJongSeung(QString jong1, QString jong2);
    //글자조합
    QString CombineKorean(QString cho, QString jung, QString jong = " ");

private slots:
    void on_btn_clicked();

    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_9_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_10_clicked();
    void on_btn_11_clicked();
    void on_btn_12_clicked();
    void on_btn_13_clicked();
    void on_btn_14_clicked();
    void on_btn_18_clicked();
    void on_btn_17_clicked();
    void on_btn_16_clicked();
    void on_btn_delete_clicked();
    void on_btn_space_clicked();
    void on_btn_backSpace_clicked();

private:
    Ui::MainWindow *ui;

    //한글 파츠 배열
    QStringList m_lChoSeung = {"ㄱ","ㄲ","ㄴ","ㄷ","ㄸ","ㄹ","ㅁ","ㅂ","ㅃ","ㅅ","ㅆ","ㅇ","ㅈ","ㅉ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"};//초성배열19
    QStringList m_lJungSeung = {"ㅏ","ㅐ","ㅑ","ㅒ","ㅓ","ㅔ","ㅕ","ㅖ","ㅗ","ㅘ","ㅙ","ㅚ","ㅛ","ㅜ","ㅝ","ㅞ","ㅟ","ㅠ","ㅡ","ㅢ","ㅣ"};//중성배열21
    QStringList m_lJongSeung = {" ","ㄱ","ㄲ","ㄳ","ㄴ","ㄵ","ㄶ","ㄷ","ㄹ","ㄺ","ㄻ","ㄼ","ㄽ","ㄾ","ㄿ","ㅀ","ㅁ","ㅂ","ㅄ","ㅅ","ㅆ","ㅇ","ㅈ","ㅊ","ㅋ","ㅌ","ㅍ","ㅎ"};//종성배열28

    //입력된 글자 QUEUE
    QString queueStr;
};
#endif // MAINWINDOW_H
