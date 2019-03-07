#include "dataH/mainwindow.h"
#include "../ui_mainwindow.h"
#include "dataH/utilties.h"
#include "dataH/grammar.h"
#include "dataH/allrecords.h"
#include "dataH/record.h"
#include "dataH/recordmanager.h"
#include "dataH/resultrecord.h"
#include "dataH/grammartest.h"
#include "includes.h"

QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTextEdit)



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui-> setupUi(this);
    this -> setWindowTitle("DATA Query Analyser ");
    ui->sqlEdit -> setFocus();






    /***************************************************************************************************
                                    Zone de creation de bouton
      Information : QPushButton émet un signal si un event se produit(Manipuler un bouton paar exemple)
     ***************************************************************************************************/
}

MainWindow::~MainWindow()
{
    delete ui;
}

     /******************************************************************************************
            Zone de definiton des fonctions : affichage de l'action du clique sur le bouton
     *****************************************************************************************/


void MainWindow::on_clearButton_clicked()
{

    // pour activer un bouton il faut mettre avant
    // ui -> (le nom du composant )
    ui->sqlEdit -> clear();
    ui->sqlEdit -> setFocus();
}


void MainWindow::on_loadButton_clicked()
{
    // create a template for all the records
    // AllRecords allRecords;

    // load the file
    QFileInfo file(QFileDialog::getOpenFileName(this, "titre", "../testApplication/DB"));
    // get the name of the file
    std::string file_name = file.fileName().toStdString();
    // get the path of the file
    std::string file_path = file.filePath().toStdString();
    // change the format of the file_name to show it in our table
    QString file_n = stToQs(file_name);
    ui->dataBaseShow -> setText(file_n);

    // parsing all the data
    makeTheDeal(file_path);

    // afficher toute les donnée !!
    // AllRecords::testShowData();



}



void MainWindow::on_ASTButton_clicked()
{
    // pour afficher l'ast sur l'onglet ast de l'app
    ui->astField -> setText("Abstract Syntax Tree.... ");
    // affiche les donnée dans le debugger !!
    AllRecords::testShowData();

    // try to show the data :

    QList<Record> data = AllRecords::getAllRecors();    // get all the data
    int taille = data.length();     // get the length of our allRecords
    ui->sdLWidget -> setRowCount(taille);

    for(auto i=0; i< taille; i++){
        Record r = data.at(i);
        int j=0;
        QString s = QString::number(r.sqid);
        ui->sdLWidget -> setItem(i,j, new QTableWidgetItem(s));
        ui->sdLWidget -> setItem(i,j+1, new QTableWidgetItem(r.headquater));
        ui->sdLWidget -> setItem(i,j+2, new QTableWidgetItem(r.industry));
        ui->sdLWidget -> setItem(i,j+3, new QTableWidgetItem(r.position.join(";")));
        ui->sdLWidget -> setItem(i,j+4, new QTableWidgetItem(r.opening.join(";")));
        ui->sdLWidget -> setItem(i,j+5, new QTableWidgetItem(r.closing.join(";")));

    }


    ui->sdLabel-> setFocus();

}



// exec function !!


void MainWindow::on_ExecButton_clicked()
{

    // create our ast tree in the first !!
    dataSQL::selectStmt emp;
    // data show
    ui->dataShow -> setText(" data coming soon ... O_O! ");
    // Get the data from the text field
    QString inputx = ui->sqlEdit->toPlainText();
    // make the data from Qstring Object of Qt to string from C++ that we needs to boost
    std::string data = inputx.toUtf8().constData();


    // call the function to parse the data with : sql request and the the output emp
    bool isOk = doParse(data, emp);

    if(!isOk){
        // pour afficher le " parsing failed "
        ui->parsingShow -> setText("Parsing Failed !!");
    }
    else{
           // pour afficher le " parsing Succéess " and print data
        ui->parsingShow -> setText("Parsing succeeded !!");

        dataSQL::selectFromStmt selectFromS;
        dataSQL::project_list project_l;
        dataSQL::col_predicate col_pred;
        dataSQL::col_projection col_project;
        dataSQL::predicate_ref ref_pred;
        dataSQL::col_reference col_ref;
        dataSQL::ref_type_0 ref_type_0;
        dataSQL::ref_type_1 ref_type_1;
        dataSQL::ref_type_2 ref_type_2;
        dataSQL::ref_type_3 ref_type_3;
        dataSQL::value value_v;



        // **************** switch tables ******************
        selectFromS = emp.query;                    // switch to selectFromStmt
        project_l = selectFromS.columns;                // to projectList
        col_project = project_l.col_project;            // to col projection
        ref_pred = col_project.pred_ref;                // to the variante of predicate and col reference

        // use apply visitor to switch between the variant

        int check = boost::apply_visitor(dataSQL::testP(), ref_pred);
        if(check == 1){
            qDebug() << "col_predi";
            col_pred = boost::get<dataSQL::col_predicate>(ref_pred);        // get The col_predicate
            col_ref = col_pred.col_ref;                                     // get the col_reference
        }
        else if(check == 2){
            qDebug() << "col_ref" ;
            col_ref = boost::get<dataSQL::col_reference>(ref_pred);         // get the col_red
        }


        std::string c, s, ed;
        std::string v = "";
        int start = 0, end = 0;
        QString col_name;
        int check_ = boost::apply_visitor(dataSQL::testC(), col_ref.col_ref_variant);

        if(check_ == 0){
            ref_type_0 = boost::get<dataSQL::ref_type_0>(col_ref.col_ref_variant);
        }
        if(check_ == 1){
            ref_type_1 = boost::get<dataSQL::ref_type_1>(col_ref.col_ref_variant);
            ref_type_0= ref_type_1.ref_type_0;
            start = ref_type_1.getStart();
        }
        if(check_ == 2){
            ref_type_2 = boost::get<dataSQL::ref_type_2>(col_ref.col_ref_variant);
            ref_type_0= ref_type_2.ref_type_0;
            end = ref_type_2.getEnd();
        }
        if(check_ == 3){
            ref_type_3 = boost::get<dataSQL::ref_type_3>(col_ref.col_ref_variant);
            ref_type_0= ref_type_3.ref_type_0;
            start = ref_type_3.getStart();
            end = ref_type_3.getEnd();
        }


        value_v = col_pred.value;
        int _check_ = boost::apply_visitor(dataSQL::testD(), value_v.value_variant);
        if(_check_ == 0){
            v = boost::get<std::string>(value_v.value_variant);
        }
        if(_check_ == 1){
            int r = boost::get<int>(value_v.value_variant);
            v  = std::to_string(r);
        }




        // *************************** get the different fields *******************
        // ----------------------- penser a faire une fonction pour avoir tout en même temps au lieu de un a la fois

        std::string t = selectFromS.getTable();                         // get the table name
        c = ref_type_0.getCol();                                        // get the col_name
        std::string p = col_pred.getPredicate();                          // get the value

        // ************************ convert *******************
        // ----------------------- penser a faire une fonction pour avoir tout en même temps au lieu de un a la fois

        QString table_name = QString::fromUtf8(t.c_str());              // convert
        col_name = QString::fromUtf8(c.c_str());                          // convert
        QString value = QString::fromUtf8(v.c_str());
        //
        QString predicate = QString::fromUtf8(p.c_str());

        // ********************** show ast *********************


        qDebug() << " table : " << table_name << "\n colonne :" << col_name
                 << "\n [start : end ] : [" << start << ":" << end << "]"
                 << "\n predicate : " << predicate << "\n value : " << value ;





        // show the Abstract syntax tree
        // still some problems with showing the integers
        ui->astField -> setText(" AST : [ \n col_Projection = [ " + col_name + " ] \n [ start : end ] = [ " + QString::fromUtf8(std::to_string(start).c_str()) + " : " + QString::fromUtf8(std::to_string(end).c_str()) + " ]"
                                + "\n predicate = [ " + predicate + " ] \n value = [ " + value
                                +" ] \n table = [ " + table_name + " ] \n ]" );



        // ********************************* TRY *********************************
        AllResultRecord r;
        r = open_table(table_name);
        r = fetch_seq(col_name, r);

        // showing data in the table !
        QList<ResultRecord> data = r.getAllResultRecors();  // get all the result records
        int taille = data.length();          // get the length

        ui->dataTable-> setRowCount(taille);                // setting the rows of our table

        for(auto i=0; i< taille; i++){
            ResultRecord r = data.at(i);                    // define each Result Record of the list just above
            int j=0;
            ui->dataTable-> setItem(i,j, new QTableWidgetItem(r.table_name));
            ui->dataTable-> setItem(i,j+1, new QTableWidgetItem("1"));      // a refaire pour all_seq peut etre au lieu de parser un true, on parse 1
            ui->dataTable-> setItem(i,j+2, new QTableWidgetItem("1"));      // a refaire pour all_pos
            ui->dataTable-> setItem(i,j+5, new QTableWidgetItem(r.columns.join(";")));

        }





        // clear the query text
        ui->sqlEdit -> clear();
        // set the focus
        ui->sqlEdit -> setFocus();
    }



}


void MainWindow::on_parserTest_clicked()
{


    // create our ast tree in the first !!
    dataTSQL::selectFromStmt emp;
    // data show
    ui->dataShow -> setText(" data coming soon ... O_O! ");
    // Get the data from the text field
    QString inputx = ui->sqlEdit->toPlainText();
    // make the data from Qstring Object of Qt to string from C++ that we needs to boost
    std::string data = inputx.toUtf8().constData();


    // call the function to parse the data with : sql request and the the output emp
    bool isOk = doParse_(data, emp);

    if(!isOk){
        // pour afficher le " parsing failed "
        ui->parsingShow -> setText("Parsing Failed !!");
    }
    else{
        ui->parsingShow -> setText("Parsing successed !!");
    }
}

void MainWindow::on_pushButton_clicked()
{

}
