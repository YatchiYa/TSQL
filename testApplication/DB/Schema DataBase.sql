
# Schema of our dataBase made both with PostgreSQL and SQL Server

# create table Headerquaters

CREATE TABLE Headerquaters (
	hid integer,
	nom varchar(50),
	CONSTRAINT PK_Headerquaters PRIMARY KEY (nom)
);

# create table Industry

CREATE TABLE Industry (
	iid integer,
	nom varchar(50),
	CONSTRAINT PK_Industry PRIMARY KEY (nom)
); 

# create table position

CREATE TABLE position (
	pid integer,
	seqid integer[],
	pos integer[],
	CONSTRAINT PK_position PRIMARY KEY (pid),
	CONSTRAINT FK_position_sequences FOREIGN KEY (pid) REFERENCES stocks
);
# create table opening

CREATE TABLE opening (
	oid integer,
	op integer[],
	CONSTRAINT PK_opening PRIMARY KEY (op)
);

# create table closing

CREATE TABLE closing (
	cid integer,
	clo integer[],
	CONSTRAINT PK_closing PRIMARY KEY (clo)
);
# create table stocks

CREATE TABLE stocks (
	stid integer, 				 
	Headerquaters varchar(50),  
	Industry varchar(50),		
	position integer[],			 
	opening integer[],			
	closing integer[],			
	CONSTRAINT PK_stocks PRIMARY KEY (stid),    
	CONSTRAINT FK_sequences_opening FOREIGN KEY (opening) REFERENCES opening,	
	CONSTRAINT FK_sequences_closing FOREIGN KEY (closing) REFERENCES closing 	
);
