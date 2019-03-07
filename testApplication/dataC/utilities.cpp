// in this file we will try to handle the parsing

#include "includes.h"
#include "dataH/grammar.h"
#include "dataH/utilties.h"
#include "dataH/allrecords.h"
#include "dataH/record.h"
#include "dataH/ast.h"
#include "dataH/grammartest.h"


bool doParse(std::string str, dataSQL::selectStmt& emp){

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef dataSQL::selectStmt_parser<iterator_type> selectStmt_parser;

    selectStmt_parser g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool r = phrase_parse(iter, end, g, space, emp);

        if (r && iter == end)
        {
            return true;
        }
        else
        {
            return false;
        }

}


// this function is made in order to open the file, and treat evry thing there for the moment !!

void makeTheDeal(std::string file_path){
    Record r ;

    QString file_p = QString::fromUtf8(file_path.c_str());
    QFile file_obj(file_p);
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<<file_p;
    }
    else {

        QTextStream file_text(&file_obj);
        QString json_string;
        json_string = file_text.readAll();
        file_obj.close();
        QByteArray json_bytes = json_string.toLocal8Bit();

        auto json_doc= QJsonDocument::fromJson(json_bytes);

        if(json_doc.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        if(!json_doc.isObject()){
            qDebug()<<"JSON is not an object.";
            exit(3);
        }

        QJsonObject json_obj = json_doc.object();

        if(json_obj.isEmpty()){
            qDebug()<<"JSON object is empty.";
            exit(4);
        }



        // tous ce qui est en Haut ! est bon !!!
        // mtn on va essayer de regarder les diff champs pour notre base de donnée

             // pkoi ? pcq le fichier json est un objet ! donc on doit spécifier la premiere fois que
            // le document est un json doc Object !!

        QJsonObject root_obj = json_doc.object();

           // specifier a QT qu'il existe une variante de champs ! d'ou on utilise la hashMap
        QVariantMap root_map = root_obj.toVariantMap();

            // on sepecifie les differentes element !
            // normalement c'est la table !
        QVariantMap stocks_map = root_map["stocks"].toMap();



        QStringList key_list = stocks_map.keys();

        // the i operator : will represent the line number of our differents sequences
        for(int i=0; i < key_list.count(); ++i){   // stocks -> ids



            QString key = key_list.at(i);
            QVariantMap ids_map = stocks_map[key].toMap(); // map for each ids

            QStringList ids_list = ids_map.keys();
            for(int k=0; k < ids_list.count(); ++k){    // ids -> diferents champs

               auto tool = ids_list.at(k);

               //auto detail = ids_map[tool].toStringList() ;
               QString check = ids_map[tool].typeName();

               // on affiche les string
               if (check == "QString" ){
                   auto detail = ids_map[tool].toString();
                   //qDebug() << key << ":" << tool << ":" << detail; // showing the data !!
               }
               // on affiche les int
               if (check == "double" ){
                   auto detail = ids_map[tool].toInt();
                   //qDebug() << key << ":" << tool << ":" << detail;
               }
               // on affiche les qvariantes list
               if(check == "QVariantList"){
                   auto detail = ids_map[tool].toStringList();
                   //qDebug() << key << ":" << tool << ":" << detail;
               }


               // filing the record !!
               r.setSqid(i+1);      // id = i +1 = 0+1 car i=0 au debut
               r.setTableName("stocks");
               r.setheaderQuater(ids_map["Headquater"].toString());
               r.setIndustry(ids_map["Industry"].toString());
               r.setPosition(ids_map["position"].toStringList());
               r.setClosing(ids_map["closing"].toStringList());
               r.setOpening(ids_map["opening"].toStringList());

            }

            // filling the all records
            AllRecords::AddRecord(r);
        }

    }
}





// Qstring to String
std::string QsToSt(QString qs){
    std::string data = qs.toUtf8().constData();
    return data;
}
// string to Qstring
QString stToQs(std::string st){
    QString str = QString::fromUtf8(st.c_str());
    return str;
}






// ******************************* this is section is for trying the all parsing for the 5 querys **************************
bool doParse_(std::string str, dataTSQL::selectFromStmt& emp){

    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef dataTSQL::selectStmt_parser<iterator_type> selectStmt_parser;

    selectStmt_parser g; // Our grammar

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, g, space, emp);

        if (r && iter == end)
        {
            return true;
        }
        else
        {
            return false;
        }

}
