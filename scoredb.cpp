/**Class to handle scores management using a txt file database.
 *
 *
 *
 */

#include "scoredb.h"

ScoreDB::ScoreDB() {

    QString filePath = QCoreApplication::applicationDirPath() + "/scores.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");

            // get pieces from the split which are divided into "Name" " " "Score"
            if (parts.size() >= 2) {
                QString getName = parts[0];
                QString getScore = parts[1];
                int scoreConvert = getScore.toInt();
                scoreData *addData = new scoreData();
                addData->score=scoreConvert;
                addData->user = getName;
                existingScores.insert(addData);

            }
        file.close();
        }
    }
}

/**Method to update the scores file after game completion.
 * @brief ScoreDB::updateFile
 * @param Name - username to add
 * @param score - score to add.
 */

void ScoreDB::updateFile(QString Name, int score){
    QString filePath = QCoreApplication::applicationDirPath() + "/scores.txt";

    if (Name=="Guest") {
        return;
    }

    //write score and username to file.
    QFile file(filePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << Name << " " << score << "\n";
        file.close();

    }
    else{
        file.close();
        return;
    }
}
