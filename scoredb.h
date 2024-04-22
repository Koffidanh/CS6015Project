#ifndef SCOREDB_H
#define SCOREDB_H

#include <QString>
#include <QFile>
#include <QCoreApplication>

class ScoreDB
{
public:
    ScoreDB();
    static void updateFile(QString Name, int score);
    struct scoreData {
        QString user;
        int score;
    };
    QSet<scoreData*> existingScores;
};

#endif // SCOREDB_H
