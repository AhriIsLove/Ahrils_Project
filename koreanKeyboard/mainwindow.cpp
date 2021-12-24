#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include <QTextCodec>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    QString resultStr = "";

    //모음 조합(천지인키보드:ㅡ / . / ㅣ)
    resultStr = CombineVowles(queueStr);

    //한글조합 알고리즘
    CombineKoreanAlgorithm(&resultStr);

    ui->lbresult->setText(resultStr);
    ui->lbInput->setText(queueStr);
}

QString MainWindow::CombineVowles(QString str)
{
    for(int i=0; i<str.length();i++)
    {
        //.으로시작하는 모음
        if(str.at(i) == ".")
        {
            if(i+1 < str.length() && str.at(i+1) == ".")
            {
                str.replace(i,2, "‥");

                if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                {
                    str.replace(i,2, "ㅕ");
                }
                else if(i+1 < str.length() && str.at(i+1) == "ㅡ")
                {
                    str.replace(i,2, "ㅛ");
                }
            }
            else if(i+1 < str.length() && str.at(i+1) == "ㅣ")
            {
                str.replace(i,2, "ㅓ");

                if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                {
                    str.replace(i,2, "ㅔ");
                }
            }
            else if(i+1 < str.length() && str.at(i+1) == "ㅡ")
            {
                str.replace(i,2, "ㅗ");

                if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                {
                    str.replace(i,2, "ㅚ");

                    if(i+1 < str.length() && str.at(i+1) == ".")
                    {
                        str.replace(i,2, "ㅘ");

                        if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                        {
                            str.replace(i,2, "ㅙ");
                        }
                    }
                }
            }
        }

        //ㅣ으로시작하는 모음
        if(str.at(i) == "ㅣ")
        {
            if(i+1 < str.length() && str.at(i+1) == ".")
            {
                str.replace(i,2, "ㅏ");

                if(i+1 < str.length() && str.at(i+1) == ".")
                {
                    str.replace(i,2, "ㅑ");

                    if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                    {
                        str.replace(i,2, "ㅒ");
                    }
                }
                else if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                {
                    str.replace(i,2, "ㅐ");
                }
            }
        }

        //ㅡ으로시작하는 모음
        if(str.at(i) == "ㅡ")
        {
            if(i+1 < str.length() && str.at(i+1) == ".")
            {
                str.replace(i,2, "ㅜ");

                if(i+1 < str.length() && str.at(i+1) == ".")
                {
                    str.replace(i,2, "ㅠ");

                    if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                    {
                        str.replace(i,2, "ㅝ");

                        if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                        {
                            str.replace(i,2, "ㅞ");
                        }
                    }
                }
                else if(i+1 < str.length() && str.at(i+1) == "ㅣ")
                {
                    str.replace(i,2, "ㅟ");
                }
            }
            else if(i+1 < str.length() && str.at(i+1) == "ㅣ")
            {
                str.replace(i,2, "ㅢ");
            }
        }
    }

    return str;
}

void MainWindow::CombineKoreanAlgorithm(QString *inputStr)
{
    //for문변수
    int i,j;

    //입력된 글자가 1개이하라면 처리할 필요 없음
    if(inputStr->length() <= 1) return;

    //입력된 글자만큼 반복
    for(i=0; i<inputStr->length(); i++)
    {
        //예상글자저장
        QString cloneStr = *inputStr;

        ////i:초성확인
        for(j=0; j<m_lChoSeung.length();j++)
        {
            if(cloneStr.at(i) == m_lChoSeung[j])
            {
                //초성확인완료
                break;//초성확인종료
            }
        }
        if(j >= m_lChoSeung.length())
        {
            //초성찾지못함
            continue;//다음글자로이동후반복
        }

        ////i+1:조합초성확인->중성확인
        //현재조합 글자가 1개이하라면 처리할 필요 없음
        if(cloneStr.length()-i <= 1) return;
        //조합가능초성확인
        if(CombineChoSeung(cloneStr.at(i),cloneStr.at(i+1)) != nullptr)
        {
            //초성조합
            cloneStr.replace(i,2,CombineChoSeung(cloneStr.at(i),cloneStr.at(i+1)));
        }

        //중성확인
        for(j=0;j < m_lJungSeung.length();j++)
        {
            //초성이 조합되어 길이가 짧아졌을 경우 에러방지
            if(cloneStr.length()-i > 1 && cloneStr.at(i+1) == m_lJungSeung[j])
            {
                //중성확인완료
                break;//중성확인종료
            }
        }
        //중성찾지못함
        if(j >= m_lJungSeung.length())
        {
            continue;//다음글자로이동후반복
        }

        ////i+2:종성확인
        //현재조합 글자가 2개이하라면 처리할 필요 없음
        if(cloneStr.length()-i <= 2)
        {
            //글자완성:종성없는글자
            cloneStr.replace(i,2,CombineKorean(cloneStr.at(i), cloneStr.at(i+1)));
            *inputStr = cloneStr;
            continue;
        }
        for(j=0;j<m_lJongSeung.length();j++)
        {
            if(cloneStr.at(i+2) == m_lJongSeung[j])
            {
                //중성확인완료
                break;//중성확인종료
            }
        }
        //종성 찾기 못함
        if(j >= m_lJongSeung.length())
        {
            //글자완성:종성없는글자
            cloneStr.replace(i,2,CombineKorean(cloneStr.at(i), cloneStr.at(i+1)));
            *inputStr = cloneStr;
            continue;
        }

        ////i+3:종성조합확인
        //현재조합 글자가 3개이하라면 바로 완성
        if(cloneStr.length()-i <= 3)
        {
            cloneStr.replace(i,3,CombineKorean(cloneStr.at(i), cloneStr.at(i+1), cloneStr.at(i+2)));
            *inputStr = cloneStr;
            continue;
        }
        //중성약탈식별
        for(j=0; j<m_lJungSeung.length();j++)
        {
            if(cloneStr.at(i+3) == m_lJungSeung[j])
            {
                break;
            }
        }
        //중성약탈확인
        if(j < m_lJungSeung.length())
        {
            //약탈당함
            cloneStr.replace(i,2,CombineKorean(cloneStr.at(i), cloneStr.at(i+1)));
            *inputStr = cloneStr;

            //완성된글자확정
            queueStr = cloneStr;

            continue;
        }

        //종성조합확인
        if(CombineJongSeung(cloneStr.at(i+2), cloneStr.at(i+3)) != nullptr)
        {
            //현재조합 글자가 4개이하라면 바로 완성
            if(cloneStr.length()-i <= 4)
            {
                //조합하기전에 종성조합먼저
                cloneStr.replace(i+2,2,CombineJongSeung(cloneStr.at(i+2),cloneStr.at(i+3)));

                //조합된 종성과 글자 조합
                cloneStr.replace(i,3,CombineKorean(cloneStr.at(i), cloneStr.at(i+1), cloneStr.at(i+2)));
                *inputStr = cloneStr;
                continue;
            }

            //조합종성약탈식별
            for(j=0; j<m_lJungSeung.length();j++)
            {
                if(cloneStr.at(i+4) == m_lJungSeung[j])
                {
                    break;
                }
            }
            if(j < m_lJungSeung.length())
            {
                //전체약탈확인(ㄲ,ㅆ)
                if(CombineJongSeung(cloneStr.at(i+2), cloneStr.at(i+3)) == "ㄲ" || CombineJongSeung(cloneStr.at(i+2), cloneStr.at(i+3)) == "ㅆ")
                {
                    //피약탈자초성조합
                    cloneStr.replace(i+2,2,CombineChoSeung(cloneStr.at(i+2),cloneStr.at(i+3)));

                    //종성없이 조합
                    cloneStr.replace(i,2,CombineKorean(cloneStr.at(i), cloneStr.at(i+1)));
                    *inputStr = cloneStr;

                    //완성된글자확정
                    queueStr = cloneStr;

                    continue;
                }
                //부분약탈
                else
                {
                    //종성없이 조합
                    cloneStr.replace(i,3,CombineKorean(cloneStr.at(i), cloneStr.at(i+1), cloneStr.at(i+2)));
                    *inputStr = cloneStr;

                    //완성된글자확정
                    queueStr = cloneStr;

                    continue;
                }
            }

            //약탈자 없음
            //종성조합
            cloneStr.replace(i+2,2,CombineJongSeung(cloneStr.at(i+2),cloneStr.at(i+3)));
            //글자 조합
            cloneStr.replace(i,3,CombineKorean(cloneStr.at(i), cloneStr.at(i+1), cloneStr.at(i+2)));
            *inputStr = cloneStr;

            continue;
        }
        //종성조합불가능
        else
        {
            //조합
            cloneStr.replace(i,3,CombineKorean(cloneStr.at(i), cloneStr.at(i+1), cloneStr.at(i+2)));
            *inputStr = cloneStr;

            continue;
        }
    }

    return;
}

QString MainWindow::CombineChoSeung(QString cho1, QString cho2)
{
    //쌍자음만 초성조합가능
    if(cho1 == cho2)
    {
        if(cho1 == "ㄱ")
        {
            return "ㄲ";
        }
        if(cho1 == "ㄷ")
        {
            return "ㄸ";
        }
        if(cho1 == "ㅂ")
        {
            return "ㅃ";
        }
        if(cho1 == "ㅅ")
        {
            return "ㅆ";
        }
        if(cho1 == "ㅈ")
        {
            return "ㅉ";
        }
    }

    //해당사항 없음
    return nullptr;
}

QString MainWindow::CombineJongSeung(QString jong1, QString jong2)
{
    if(jong1 == "ㄱ")
    {
        if(jong2 == "ㄱ")
        {
            return "ㄲ";
        }
        else if(jong2 == "ㅅ")
        {
            return "ㄳ";
        }
    }
    if(jong1 == "ㄴ")
    {
        if(jong2 == "ㅈ")
        {
            return "ㄵ";
        }
        else if(jong2 == "ㅎ")
        {
            return "ㄶ";
        }
    }
    if(jong1 == "ㄹ")
    {
        if(jong2 == "ㄱ")
        {
            return "ㄺ";
        }
        else if(jong2 == "ㅁ")
        {
            return "ㄻ";
        }
        else if(jong2 == "ㅂ")
        {
            return "ㄼ";
        }
        else if(jong2 == "ㅅ")
        {
            return "ㄽ";
        }
        else if(jong2 == "ㅌ")
        {
            return "ㄾ";
        }
        else if(jong2 == "ㅍ")
        {
            return "ㄿ";
        }
        else if(jong2 == "ㅎ")
        {
            return "ㅀ";
        }
    }
    if(jong1 == "ㅂ")
    {
        if(jong2 == "ㅅ")
        {
            return "ㅄ";
        }
    }
    if(jong1 == "ㅅ")
    {
        if(jong2 == "ㅅ")
        {
            return "ㅆ";
        }
    }

    //해당사항 없음
    return nullptr;
}

QString MainWindow::CombineKorean(QString cho, QString jung, QString jong)
{
    //한글 유니코드 시작값
    uint cp = 44032;//0xAC00

    //초성판단
    for(int i=0; i<m_lChoSeung.length();i++)
    {
        //입력가능한초성발견
        if(m_lChoSeung[i] == cho)
        {
            cp += i*588;
            break;
        }
    }
    //중성판단
    for(int i=0; i<m_lJungSeung.length();i++)
    {
        //입력가능한중성발견
        if(m_lJungSeung[i] == jung)
        {
            cp += i*28;
            break;
        }
    }
    //종성판단
    for(int i=0; i<m_lJongSeung.length();i++)
    {
        //입력가능한종성발견
        if(m_lJongSeung[i] == jong)
        {
            cp += i;
            break;
        }
    }

    //완성 글자 반환
    return QString::fromUcs4(&cp, 1);
}

//ㄱ
void MainWindow::on_btn_clicked()
{
    queueStr.append("ㄱ");

    Update();
}

//ㄴ
void MainWindow::on_btn_2_clicked()
{
    queueStr.append("ㄴ");

    Update();
}

//ㄷ
void MainWindow::on_btn_3_clicked()
{
    queueStr.append("ㄷ");

    Update();
}

//ㄹ
void MainWindow::on_btn_4_clicked()
{
    queueStr.append("ㄹ");

    Update();
}

//ㅁ
void MainWindow::on_btn_5_clicked()
{
    queueStr.append("ㅁ");

    Update();
}

//ㅂ
void MainWindow::on_btn_6_clicked()
{
    queueStr.append("ㅂ");

    Update();
}

//ㅅ
void MainWindow::on_btn_9_clicked()
{
    queueStr.append("ㅅ");

    Update();
}

//ㅇ
void MainWindow::on_btn_7_clicked()
{
    queueStr.append("ㅇ");

    Update();
}

//ㅈ
void MainWindow::on_btn_8_clicked()
{
    queueStr.append("ㅈ");

    Update();
}

//ㅊ
void MainWindow::on_btn_10_clicked()
{
    queueStr.append("ㅊ");

    Update();
}

//ㅋ
void MainWindow::on_btn_11_clicked()
{
    queueStr.append("ㅋ");
    Update();
}

//ㅌ
void MainWindow::on_btn_12_clicked()
{
    queueStr.append("ㅎ");

    Update();
}

//ㅍ
void MainWindow::on_btn_13_clicked()
{
    queueStr.append("ㅍ");

    Update();
}

//ㅎ
void MainWindow::on_btn_14_clicked()
{
    queueStr.append("ㅎ");

    Update();
}

//ㅡ
void MainWindow::on_btn_18_clicked()
{
    queueStr.append("ㅡ");

    Update();
}

//ㅣ
void MainWindow::on_btn_17_clicked()
{
    queueStr.append("ㅣ");

    Update();
}

//.
void MainWindow::on_btn_16_clicked()
{
    queueStr.append(".");

    Update();
}

//지우기
void MainWindow::on_btn_delete_clicked()
{
    queueStr.clear();

    Update();
}

void MainWindow::on_btn_space_clicked()
{
    queueStr.append(" ");

    Update();
}

void MainWindow::on_btn_backSpace_clicked()
{
    //지울게 있으면
    if(queueStr.length() > 0)
    {
        //끝에꺼 1개 지운다
        queueStr.chop(1);
    }

    Update();
}
