//
// Created by Christo on 3/5/2019.
//

#include "Table.h"

/**
 * \brief a Constructor to create a new Table .
 * @param tableName is the name of the new Table.
 * @param databaseName is the name of the database that owns the new Table.
 */
Table::Table(std::string tableName, std::string databaseName) {
    this->tableName=tableName;
    tableFilePath= tableName+"_table";
    tableFile.open(tableFilePath);
    /*If the table File didnt open (because it doesnt exist yet), create
     * a file in the tableFilePath and write as the first line the path
     * of the table*/
    if(!tableFile){
        tableFile.open(tableFilePath, std::ios::out | std::ios::app);
        tableFile<<tableFilePath<<std::endl;
    }
    tableFile.close();

    //Now, open the file of the database and add a new line with the path of the
    //table file.
    tableFile.open(databaseName+"_database",std::ios::out | std::ios::app);
    if(tableFile){
        tableFile<<tableFilePath<<std::endl;
    }
    tableFile.close();
}

/**
 * \brief a Constructor used to create a new Table using a Textfile to input the
 * details of the table.
 * @param path is the filepath of the TextFile containing the instructions.
 * @param databaseName is the name of the database that is going to own the Table.
 * @param throwIfWrong is a boolean to specify if the Constructor should check if the file exist.
 */
Table::Table(std::string path, std::string databaseName, bool throwIfWrong) noexcept(false){
    std::string line;
    std::string answer;

    std::vector<std::vector<std::string>> columnVector;
    std::vector<std::string> columntempVector;

    //creates an ifstream an opens the file.

    std::ifstream input(path);


    if(throwIfWrong){
        if(!input.is_open()){

            throw WrongPathException();
        }
    }




    /*while(!input.is_open()){
        std::cout<<"\nThe file didn't open, enter the path again:";
        std::getline(std::cin,answer);
        input.open(answer);
    }*/
    if(input){
        while(getline(input,line)){
            //If the line has the signature "_table" it means that line
            //stores the name of the table.
            if(endsWith(line,"_table")){
                //The name is stored
                tableName=line.substr(0,(line.size()-6));
                //The filepath is stored
                tableFilePath=line;
                //The File for the table is created in the database
                tableFile.open(tableFilePath, std::ios::out | std::ios::app);
                tableFile<<tableFilePath<<std::endl;
                tableFile.close();
            }

            //If the line has the signature column it will be stored
            //in a Vector of string[2] where:
            /*
             * string[0] is the name of the column
             * string[1] is the description of the column
             * string[2] is the type of the column*/
            if(endsWith(line,"_column")){
                columntempVector.push_back(line);

                getline(input,line);
                columntempVector.push_back(line);

                getline(input,line);
                columntempVector.push_back(line);

                columnVector.push_back(columntempVector);
                columntempVector.clear();
            }


        }
        for(auto &tempVector : columnVector){

            //The string at array[2] contains a string with the type
            //This array is converted into a datatype and is used to select the correct Column Subclass
            DataType datatype = enumDatatypeMap.at(tempVector.at(2));
            switch (datatype){
                case INT:{
                    std::shared_ptr<Column>toRet(new ColumnInt(tempVector.at(0).substr(0,(tempVector.at(0).size()-7)),tableName,
                                                               tempVector.at(1).substr(0,(tempVector.at(0).size()-12))));
                    break;
                }
                case STRING:{
                    std::shared_ptr<Column>toRet(new ColumnString(tempVector.at(0).substr(0,(tempVector.at(0).size()-7)),tableName,
                                                                  tempVector.at(1).substr(0,(tempVector.at(0).size()-12))));
                    break;
                }
                case CHAR: {
                    std::shared_ptr<Column>toRet(new ColumnChar(tempVector.at(0).substr(0,(tempVector.at(0).size()-7)),tableName,
                                                                tempVector.at(1).substr(0,(tempVector.at(0).size()-12))));
                    break;
                }
                case BOOL: {
                    std::shared_ptr<Column>toRet(new ColumnBool(tempVector.at(0).substr(0,(tempVector.at(0).size()-7)),tableName,
                                                                tempVector.at(1).substr(0,(tempVector.at(0).size()-12))));
                    break;
                }
                case DOUBLE:{
                    std::shared_ptr<Column>toRet(new ColumnDouble(tempVector.at(0).substr(0,(tempVector.at(0).size()-7)),tableName,
                                                                  tempVector.at(1).substr(0,(tempVector.at(0).size()-12))));
                    break;
                }
            }
        }


    }
    input.close();

    //Now, open the file of the database and add a new line with the path of the
    //table file.
    tableFile.open(databaseName+"_database",std::ios::out | std::ios::app);
    if(tableFile){
        tableFile<<tableFilePath<<std::endl;
    }
    tableFile.close();
}

/**
 * \brief method used to refresh the vectors that contain the information stored in the file of the
 * Table.
 */
void Table::refreshTableInfo() {
    std::string databaseInfo;
    tableFile.open(tableFilePath,std::ios::in);
    if(tableFile){
        tableInfoVector.clear();
        while(tableFile>>databaseInfo){
            tableInfoVector.push_back(databaseInfo);
        }
    }
    tableFile.close();
    tableColumnVector = getColumns();
}

/**
 * \brief method use to retrieve the name of the Table.
 * @param withoutSignature isa boolean that specifies if the name should contain the
 * signature "_table" or not.
 * @return the name of the Table.
 */
std::string Table::getTableName(bool withoutSignature){
    refreshTableInfo();
    if(withoutSignature){
        for(std::string info : tableInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_table")){
                return info.substr(0,(info.size()-6));
            }
        }
        std::cout<<"\nThe table has no name";
    }else{
        for(std::string info : tableInfoVector){
            //std::cout<<info<<"\n";
            if(endsWith(info,"_table")){
                return info;
            }
        }
        std::cout<<"\nThe table has no name";
    }
}
/**
 * \brief method used to return a vector containing the filepaths of the Columns of the Table.
 * @return a vector of string containing the filepaths of the Columns.
 */
std::vector<std::string> Table::getColumns() {
    std::vector<std::string> toRet;
    for(std::string column : tableInfoVector){
        //std::cout<<info<<"\n";
        if(endsWith(column,"_column")){

            toRet.push_back(column);
        }
    }
    return  toRet;
}

/**
 * \brief method used to add a new row to the Table.
 * @param stringVector is a vector of strings that contains the values for every single Column.
 */
void Table::addRow (std::vector<std::string> stringVector){
    DataType type;
    int counter = 0;
    std::shared_ptr<Column>columnDerive;
    refreshTableInfo();
    for(std::string colpath: getColumns()){

        std::shared_ptr<Column>tempColumn(new Column(colpath));
        type = tempColumn->getType();
        switch (type){
            case INT:{
                columnDerive = std::shared_ptr<ColumnInt>(new ColumnInt(colpath));

                break;
            }
            case STRING:{
                columnDerive=std::shared_ptr<ColumnString>(new ColumnString(colpath));
                break;
            }
            case CHAR: {
                columnDerive=std::shared_ptr<ColumnChar>(new ColumnChar(colpath));
                break;
            }
            case BOOL: {
                columnDerive=std::shared_ptr<ColumnBool>(new ColumnBool(colpath));
                break;
            }
            case DOUBLE:{
                columnDerive=std::shared_ptr<ColumnDouble>(new ColumnDouble(colpath));
                break;
            }
        }

        columnDerive->addData(stringVector.at(counter));
        counter++;
    }

}

/**
 * \brief method used to receive the values of every single Column that the table has.
 * @return a vector of strings with the values entered by the user.
 */
std::vector<std::string> Table::getRowFromUser(){
    DataType type;
    std::string tempString;
    std::vector<std::string>toRet;
    for(std::string colpath: getColumns()){
        std::shared_ptr<Column>columnDerive(new Column(colpath));
        std::cout<<"\nEnter the "<<columnDerive->getColumnName(true);


        type = columnDerive->getType();
        switch (type){
            case INT:{

                int condition;

                std::getline(std::cin,tempString);

                condition=validateInt(tempString);
                tempString = std::to_string(condition);

                break;
            }
            case STRING:{
                std::string condition;

                std::getline(std::cin,condition);
                tempString = condition;

                break;
            }
            case CHAR: {
                char condition;

                std::getline(std::cin,tempString);
                condition = tempString.at(0);
                tempString = condition;
                break;
            }
            case BOOL: {
                std::string condition;

                std::getline(std::cin,tempString);
                condition = validateBool(tempString);
                tempString = condition;
                break;
            }
            case DOUBLE:{
                double condition;

                std::getline(std::cin,tempString);
                condition=validateDouble(tempString);
                std::string str = std::to_string (condition);
                str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
                if(str.back()=='.'){
                    str = str.substr(0, str.size()-1);
                }
                tempString = str;
                break;
            }
        }


        toRet.push_back(tempString);
    }
    return toRet;
}

/**
 * \brief method used to print in Console all the Columns that this Table posses.
 * @param enumerated
 */
void Table::printColumn(bool enumerated) {
    if(enumerated){
        int i=0;
        for(std::string data : tableColumnVector){
            std::cout<<"\n["<<i++<<"]"<<data;
        }
    }else{
        for(std::string col : getColumns()){
            std::cout<<"\n"<<col;
        }
    }
}

/**
 * \brief mehtod used to delete all the Columns of the table.
 */
void Table::deleteAllColumns(){
    for(std::string columnName:tableColumnVector){
        deleteColumn(std::shared_ptr<Column>(new Column(columnName)));
    }
}

/**
 * \brief method used to delete a specific column from the table.
 * @param column is the Column to be deleted from the table.
 */
void Table::deleteColumn(std::shared_ptr<Column>column) {
    std::string col = column->getColumnFilePath();
    tableFile.open(tableFilePath, std::ios::in);
    std::ofstream  temp;
    temp.open("temp.txt");

    std::string line;
    while(tableFile>>line){
        if(line!=col){
            temp<<line<<std::endl;
        }
    }
    tableFile.close();
    temp.close();
    remove((tableFilePath).c_str());
    rename("temp.txt",(tableFilePath).c_str());
    std::remove((col).c_str());
}

/**
 * \brief method used to get the filepath of the table.
 * @return the filepath of the table.
 */
const std::string &Table::getTableFilePath() const {
    return tableFilePath;
}

/**
 * \brief a Constructor used to open an existant Table from the files stored in the program.
 * @param tableFilePath is the filepath to the table file.
 */
Table::Table(std::string tableFilePath) {
    this->tableFilePath = tableFilePath;
    this->tableName = getTableName(true);
    this->tableColumnVector = getColumns();
}

/**
 * \brief method used to create a new query event where the user
 * must specify the Columns needed and the conditions of the query
 * For example, if the user wants the name of the students which age is 22
 * the user must select the Column "firstName" and enter a condition such as
 * Age == 2. Then, the user must specify if she/he wants to export the result to a
 * file or to see the result in the Console.
 */
void Table:: query(){
    std::string tempString;
    refreshTableInfo();
    int answer;
    std::vector<std::vector<std::string>>queryArray;
    std::shared_ptr<Column>tempColumn;
    std::vector<std::string> tableColumns = getColumns();
    std::vector<std::string> queryColumns;
    std::vector<std::string> queryResult;
    std::vector<std::string> conditionVector;
    std::map<std::string,std::string> conditionMap;
    std::vector<bool> isqueryVector;
    int counter1 = 0;
    int counter2;
    std::string tempColPath;
    DataType type;

    //The Columns to query are selected by the user
    while(true){
        //this counter is used to display the Continue option once there has been at least one selection
        //of column
        counter1++;
        counter2=0;
        std::cout<<"Select the columns to query: ";
        std::cout<<"\n[0] All";
        for(std::string colpath: tableColumns){
            counter2++;

            tempColumn = std::shared_ptr<Column>(new Column(colpath));

            tempColumn->refreshColumnInfo();



            std::cout<<"\n["<<counter2<<"]"<<tempColumn->getColumnName(true);
            if(counter1==1){
                queryArray.push_back(tempColumn->columnInfoVector);
                conditionMap.insert(std::pair<std::string,std::string>(colpath,"null"));
            }

        }
        if(counter1>1){
            std::cout<<"\n[C]Continue";
        }
        std::getline(std::cin,tempString);
        if(tempString=="c" || tempString=="C"){
            break;
        }
        answer=validateAnswerRange(getColumns().size(),tempString);
        if(answer==0){
            queryColumns=getColumns();
            break;
        }else{
            queryColumns.push_back(tableColumns.at(answer-1));
            tableColumns.erase(tableColumns.begin()+validateAnswerRange(tableColumns.size(),tempString)-1);
        }
    }

    /*std::cout<<"\nQueryColumns";
    for(std::string colpath: queryColumns){
        std::cout<<"\n"<<colpath;
    }*/



    //tableColumns is reset so we can iterate again over it to select the conditions of the query from all
    //the Columns of the table
    tableColumns=getColumns();

    /*The conditions of the query are selected. The conditions are similar to the WHERE function in MySQL
     * At the end of this While loop, the string vector 'conditionVector' will be contain the query conditions
     * of the columns, if no condition was specified the default is ""
     * */

    while(true){

        counter2=-1;
        std::cout<<"\nSelect the column to add condition: ";

        for(std::string colpath: tableColumns){
            counter2++;

            tempColumn = std::shared_ptr<Column>(new Column(colpath));

            tempColumn->refreshColumnInfo();

            std::cout<<"\n["<<counter2<<"]"<<tempColumn->getColumnName(true);

        }
        std::cout<<"\n[C]Continue";
        std::getline(std::cin,tempString);

        if(tempString=="c" || tempString=="C"){
            break;
        }

        answer=validateAnswerRange(tableColumns.size()-1,tempString);

        tempColumn = std::shared_ptr<Column>(new Column(tableColumns.at(answer)));
        tempColPath=tableColumns.at(answer);

        type = tempColumn->getType();

        tableColumns.erase(tableColumns.begin()+validateAnswerRange(tableColumns.size()-1,tempString));

        switch (type){
            case INT:{

                int condition;
                std::cout<<"\nEnter the condition:";
                std::getline(std::cin,tempString);

                condition=validateInt(tempString);
                conditionMap[tempColPath] = std::to_string(condition);

                break;
            }
            case STRING:{
                std::string condition;
                std::cout<<"\nEnter the condition:";
                std::getline(std::cin,condition);
                conditionMap[tempColPath] = condition;

                break;
            }
            case CHAR: {
                char condition;
                std::cout<<"\nEnter the condition:";
                std::getline(std::cin,tempString);
                condition = tempString.at(0);
                conditionMap[tempColPath] = condition;
                break;
            }
            case BOOL: {
                std::string condition;
                std::cout<<"\nEnter the condition:";
                std::getline(std::cin,tempString);
                condition = validateBool(tempString);
                conditionMap[tempColPath] = condition;
                break;
            }
            case DOUBLE:{
                double condition;
                std::cout<<"\nEnter the condition:";
                std::getline(std::cin,tempString);
                condition=validateDouble(tempString);
                std::string str = std::to_string (condition);
                str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
                if(str.back()=='.'){
                    str = str.substr(0, str.size()-1);
                }
                conditionMap[tempColPath] = str;
                break;
            }
        }

    }
    /*std::cout<<"\nconditionMap: size "<<conditionMap.size();
    for(std::pair<std::string,std::string> pair:conditionMap){
        std::cout<<"\n"<<pair.first<<"-"<<pair.second;
    }*/

    for(std::string colpath: getColumns()){
        conditionVector.push_back(conditionMap[colpath]);
    }

    /*std::cout<<"\nconditionVector: size "<<conditionVector.size();
    for(std::string str :conditionVector){
        std::cout<<"\n"<<str;
    }*/


    try{

        //std::cout<<"\nG0";
        for(int i = 0;i<queryArray.at(0).size()-startPointColumn;i++){
            //std::cout<<"\nG1";
            tempString="";

            bool isquery=true;
            //std::cout<<"\nG2";
            for(int j = 0; j<queryArray.size();j++){
                //std::cout<<"\nG3";
                std::string tempstr;
                //std::cout<<"\ncondition vector at "<<j<<" ";
                //std::cout<<conditionVector.at(j);
                //std::cout<<"\nS15 i= "<<i<<" j="<<j<<" numCol="<<queryArray.size()<<" numData="<<queryArray.at(0).size();
                if(conditionVector.at(j)!="null"){
                    //std::cout<<"\nG4";
                    isquery = isquery && (queryArray.at(j).at(i+startPointColumn)==conditionVector.at(j));
                    //std::cout<<"\n"<<queryArray.at(j).at(i+startPointColumn)<<" = "<<conditionVector.at(j);
                }
            }
            //std::cout<<"\nG5";
            try{
                //std::cout<<"\nG6";

                isqueryVector.push_back(isquery);
                //std::cout<<"\nG7";
            }catch (const std::exception &exc){
                std::cerr<<exc.what();
            }


        }
        //std::cout<<"\nG8";


    }catch(std::exception &x){
        std::cerr << x.what();
    }





    queryArray.clear();

    //The queryArray is populated with only the columns that where selected by the user
    for(std::string colpath: queryColumns){
        counter2++;
        //std::cout<<"\nX "<<colpath;

        tempColumn = std::shared_ptr<Column>(new Column(colpath));

        tempColumn->refreshColumnInfo();

        queryArray.push_back(tempColumn->columnInfoVector);

    }




    std::cout<<"Do you want to see result in Console or Export to file?"
               "\n[0] Console"
               "\n[1] Export to File";
    std::getline(std::cin, tempString);
    if(isYes(tempString)){
        std::fstream exportFile;
        //The result is exported to a file
        std::cout<<"\nEnter a name for the Export file: ";
        std::getline(std::cin,tempString);

        exportFile.open(tempString);
        if(!exportFile){
            exportFile.open(tempString, std::ios::out | std::ios::app);

            for(std::string colpath: queryColumns){

                tempColumn = std::shared_ptr<Column>(new Column(colpath));

                tempColumn->refreshColumnInfo();

                exportFile<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempColumn->getColumnName(true);

            }
            exportFile<<std::endl;

            //This nested for loop prints the result of the query
            //The first loop iterates over the data entries (the rows)
            //The second one iterates over the columns
            for(int i = 0;i<queryArray.at(0).size()-startPointColumn;i++){

                for(int j = 0; j<queryArray.size();j++){
                    std::string rowString;
                    std::string tempstr;
                    tempstr = queryArray.at(j).at(i+startPointColumn);
                    if(isqueryVector.at(i)){
                        exportFile<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempstr;
                    }


                }
                exportFile<<std::endl;


            }
        }

        exportFile.close();

    }else{
        std::cout<<"\nQuery result: \n";

        for(std::string colpath: queryColumns){

            tempColumn = std::shared_ptr<Column>(new Column(colpath));

            tempColumn->refreshColumnInfo();

            std::cout<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempColumn->getColumnName(true);

        }
        std::cout<<std::endl;

        //This nested for loop prints the result of the query
        //The first loop iterates over the data entries (the rows)
        //The second one iterates over the columns
        for(int i = 0;i<queryArray.at(0).size()-startPointColumn;i++){

            for(int j = 0; j<queryArray.size();j++){
                std::string rowString;
                std::string tempstr;
                tempstr = queryArray.at(j).at(i+startPointColumn);
                if(isqueryVector.at(i)){
                    std::cout<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempstr;
                }


            }
            std::cout<<std::endl;


        }
    }


   /* std::cout<<"\nisqueryVector: ";
    for(bool colpath:isqueryVector){
        std::cout<<"\n"<<colpath;
    }

    std::cout<<"\nQueryComuns: ";
    for(std::string colpath: queryColumns){
        std::cout<<"\n"<<colpath;
    }*/



}
/**
 * \brief method used to print all the data stored in the Table in the Console.
 */
void Table::showTable(){


    std::vector<std::vector<std::string>>queryArray;

    std::shared_ptr<Column>tempColumn;
    //The new export file is created and opened

    //This for loop iterates over the columns of the table to create a vector with the information of every column
    //Then, each vector is stored in a vector of vectors called queeyArray
    for(std::string colpath: getColumns()){

        tempColumn = std::shared_ptr<Column>(new Column(colpath));

        tempColumn->refreshColumnInfo();

        queryArray.push_back(tempColumn->columnInfoVector);


        std::cout<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempColumn->getColumnName(true);

        /*if(tempColumn->getColumnName(true).size()<8){
            std::cout<<tempColumn->getColumnName(true)<<",\t\t\t";
        }else if(tempColumn->getColumnName(true).size()<16){
            std::cout<<tempColumn->getColumnName(true)<<",\t\t";
        }else{
            std::cout<<tempColumn->getColumnName(true)<<",\t";
        }*/


    }

    std::cout<<std::endl;


    //By last, the information is written in the export file in format "CSV"
    for(int i = 0;i<queryArray.at(0).size()-startPointColumn;i++){

        for(int j = 0; j<queryArray.size();j++){
            std::string tempstr;
            //std::cout<<"\nS15 i= "<<i<<" j="<<j<<" numCol="<<queryArray.size()<<" numData="<<queryArray.at(0).size();
            if(j+1<queryArray.size()){
                //tempstr = queryArray.at(j).at(i+startPointColumn);
                std::cout<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<queryArray.at(j).at(i+startPointColumn);

                /*if(tempstr.size()<8){
                    std::cout<<tempstr<<",\t\t\t";
                }else if(tempstr.size()<16){
                    std::cout<<tempstr<<",\t\t";
                }else{
                    std::cout<<tempstr<<",\t";
                }*/
                //std::cout<<"\nS16 i= "<<i<<" j="<<j<<" size="<<queryArray.size()<<" numData="<<queryArray.at(0).size();
            }else{
                std::cout<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<queryArray.at(j).at(i+startPointColumn);
                //tempstr = queryArray.at(j).at(i+startPointColumn);
                /*if(tempstr.size()<8){
                    std::cout<<tempstr<<"\t\t";
                }else if(tempstr.size()<16){
                    std::cout<<tempstr<<"\t";
                }else{
                    std::cout<<tempstr;
                }*/
                //std::cout<<"\nS17 i= "<<i<<" j="<<j<<" size="<<queryArray.size()<<" numData="<<queryArray.at(0).size();

            }


        }

        std::cout<<std::endl;
        std::cout<<std::endl;
    }
}

/**
 * \brief method used to create a new TextFile and save the column into the  new file.
 * \note the query option wasn't implemented because a new method called query() solves that
 * problem in a better way.
 * @param name is the name of the new file.
 * @param query is the condition to export the data.
 */
void Table::exportFile(std::string name, std::string query){
    std::fstream exportFile;

    std::vector<std::vector<std::string>>queryArray;

    std::shared_ptr<Column>tempColumn;
    //The new export file is created and opened


    exportFile.open(name);
    if(!exportFile){
        exportFile.open(name, std::ios::out | std::ios::app);

        int counter = 0;

        //If the string query = "all" all the information of the table will be printed
        if(query=="all"){

            //The table is refreshed to populate TableInfoVector with the information stored in the file of the table.
            refreshTableInfo();


            //This for loop iterates over the columns of the table to create a vector with the information of every column
            //Then, each vector is stored in a vector of vectors called queeyArray
            for(std::string colpath: getColumns()){

                tempColumn = std::shared_ptr<Column>(new Column(colpath));

                tempColumn->refreshColumnInfo();

                queryArray.push_back(tempColumn->columnInfoVector);


                /*if(tempColumn->getColumnName(true).size()<8){
                    exportFile<<tempColumn->getColumnName(true)<<",\t\t\t";
                }else if(tempColumn->getColumnName(true).size()<16){
                    exportFile<<tempColumn->getColumnName(true)<<",\t\t";
                }else{
                    exportFile<<tempColumn->getColumnName(true)<<",\t";
                }*/

                exportFile<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<tempColumn->getColumnName(true);




            }

            exportFile<<std::endl;


            //By last, the information is written in the export file in format "CSV"
            for(int i = 0;i<queryArray.at(0).size()-startPointColumn;i++){

                for(int j = 0; j<queryArray.size();j++){
                    std::string tempstr;
                    //std::cout<<"\nS15 i= "<<i<<" j="<<j<<" numCol="<<queryArray.size()<<" numData="<<queryArray.at(0).size();
                    if(j+1<queryArray.size()){
                        exportFile<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<queryArray.at(j).at(i+startPointColumn)<<",";
                        /*tempstr = queryArray.at(j).at(i+startPointColumn);
                        if(tempstr.size()<8){
                            exportFile<<tempstr<<",\t\t\t";
                        }else if(tempstr.size()<16){
                            exportFile<<tempstr<<",\t\t";
                        }else{
                            exportFile<<tempstr<<",\t";
                        }*/
                        //std::cout<<"\nS16 i= "<<i<<" j="<<j<<" size="<<queryArray.size()<<" numData="<<queryArray.at(0).size();
                    }else{
                        exportFile<<std::left<<std::setw(cellWidht)<<std::setfill(separator)<<queryArray.at(j).at(i+startPointColumn);
                        /*tempstr = queryArray.at(j).at(i+startPointColumn);
                        if(tempstr.size()<8){
                            exportFile<<tempstr<<"\t\t";
                        }else if(tempstr.size()<16){
                            exportFile<<tempstr<<"\t";
                        }else{
                            exportFile<<tempstr;
                        }*/
                        //std::cout<<"\nS17 i= "<<i<<" j="<<j<<" size="<<queryArray.size()<<" numData="<<queryArray.at(0).size();

                    }


                }

                exportFile<<std::endl;
                std::cout<<std::endl;
            }
        }
    }

    exportFile.close();
}

