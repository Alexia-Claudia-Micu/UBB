USE Yelp_Reviews
Go

-- a. modify the type of column

CREATE OR ALTER PROC changeAdLength
AS
BEGIN
	ALTER TABLE Ad
	ALTER COLUMN Length VARCHAR(10)
	PRINT 'ALTER TABLE Ad FROM FLOAT TO VARCHAR'
END
GO

-- a. undo

CREATE OR ALTER PROC UNDOchangeAdLength
AS
BEGIN
	ALTER TABLE Ad
	ALTER COLUMN Length DECIMAL(10,2)
	PRINT 'UNDO ALTER TABLE Ad FROM VARCHAR TO FLOAT'
END
GO

-- b. add/remove a column

CREATE OR ALTER PROC REMOVEAdVideo
AS
BEGIN
	ALTER TABLE Ad
	DROP COLUMN Video
	PRINT 'ALTER TABLE Ad DROP COLUMN Length from Ad'
END
GO

-- b. undo

CREATE OR ALTER PROC UNDOREMOVEAdVideo
AS
BEGIN
	ALTER TABLE Ad
	ADD Video VARCHAR(100)
	PRINT 'ALTER TABLE Ad ADD COLUMN Video'
END
GO

-- c. add/remove a DEFAULF constraint

CREATE OR ALTER PROC AddDefaultConstraintAdVideo
AS
BEGIN
	ALTER TABLE Ad
	ADD CONSTRAINT default_VideoLink DEFAULT '-' for Video
	PRINT 'ALTER TABLE Ad ADD CONSTRAINT DEFAULT - for VIDEO'
END
Go

-- c. UNDO

CREATE OR ALTER PROC UNDOAddDefaultConstraintAdVideo
AS
BEGIN
	ALTER TABLE Ad
	DROP CONSTRAINT default_VideoLink
	PRINT 'ALTER TABLE Ad DROP CONSTRAINT DEFAULT - for VIDEO'
END
Go

-- d.add/remove a primary key

CREATE OR ALTER PROC RemovePrimaryKeyAd
AS
BEGIN
	ALTER TABLE Ad
	DROP CONSTRAINT PK_Ad_aid
	PRINT 'ALTER TABLE Ad DROP CONSTRAINT PK_Ad_aid from Ad'
END
GO

-- d. undo

CREATE OR ALTER PROC UNDORemovePrimaryKeyAd
AS
BEGIN
	ALTER TABLE Ad
	ADD CONSTRAINT PK_Ad_aid PRIMARY KEY (aid)
	PRINT 'ALTER TABLE Ad ADD CONSTRAINT PK_Ad_aid PRIMARY KEY (aid)'
END
GO

-- e. add/remove a candidate key
CREATE OR ALTER PROC AddCandidateKeyDepartment
AS
BEGIN
	ALTER TABLE Department
	ADD CONSTRAINT UQ_Department_Name UNIQUE(DepartmentName)
	PRINT 'ALTER TABLE Department ADD CONSTRAINT UQ_Department_Name(DepartmentName)'
END
GO

-- e. undo

CREATE OR ALTER PROC UNDOAddCandidateKeyDepartment
AS
BEGIN
	ALTER TABLE Department
	DROP CONSTRAINT UQ_Department_Name
	PRINT 'ALTER TABLE Department DROP CONSTRAINT UQ_Department_Name'
END
GO

-- f. add/remove a foreign key
CREATE OR ALTER PROC RemoveForeignKeySponsor
AS
BEGIN
	ALTER TABLE Sponsors
	DROP CONSTRAINT Person_id
	PRINT 'ALTER TABLE Sponsors DROP CONSTRAINT Person'
END
GO

-- f. undo

CREATE OR ALTER PROC UNDORemoveForeignKeySponsor
AS
BEGIN
	ALTER TABLE Sponsors
	ADD CONSTRAINT Person_id FOREIGN KEY (Person) REFERENCES Person(pid) 
	PRINT 'ALTER TABLE Sponsors ADD CONSTRAINT Person FOREING KEY (Person_id) REFERENCES Person(pid)'
END
GO

-- g. create/drop a table
CREATE OR ALTER PROC CreateTestTable
AS
BEGIN
	CREATE TABLE TestTable
	(testId int NOT NULL PRIMARY KEY,
	testMessage VARCHAR(50),
	testName CHAR(30),
	testResult BIT DEFAULT 1)
	print 'CREATE TALE TestTable'
END
GO
-- g. undo
CREATE OR ALTER PROC UNDOCreateTestTable
AS
BEGIN
	DROP TABLE IF EXISTS TestTable
	PRINT 'DROP TABLE IF EXISTS TestTable'
END
Go


-- RUN a
exec changeAdLength
exec UNDOchangeAdLength

select * from ad

-- RUN b

EXEC REMOVEAdVideo
EXEC UNDOREMOVEAdVideo

select * from Ad

-- RUN c

EXEC AddDefaultConstraintAdVideo
select * from Ad

EXEC UNDOAddDefaultConstraintAdVideo
select * from Ad

-- RUN d

EXEC RemovePrimaryKeyAd
EXEC UNDORemovePrimaryKeyAd
select * from ad

-- RUN e

EXEC AddCandidateKeyDepartment
EXEC UNDOAddCandidateKeyDepartment

-- RUN f
EXEC RemoveForeignKeySponsor
EXEC UNDORemoveForeignKeySponsor

-- RUN g
EXEC CreateTestTable
EXEC UNDOCreateTestTable




drop TABLE VersionChanged
CREATE TABLE VersionChanged
	(currentProcedure VARCHAR(100),
	backwardsProcedure VARCHAR(100),
	versionTO INT UNIQUE)
GO

INSERT INTO VersionChanged(currentProcedure,backwardsProcedure,versionTO)
VALUES ('changeAdLength', 'UNDOchangeAdLength', 1),
('REMOVEAdVideo', 'UNDOREMOVEAdVideo', 2),
('AddDefaultConstraintAdVideo','UNDOAddDefaultConstraintAdVideo', 3),
('RemovePrimaryKeyAd','UNDORemovePrimaryKeyAd', 4),
('AddCandidateKeyDepartment', 'UNDOAddCandidateKeyDepartment', 5),
('RemoveForeignKeySponsor', 'UNDORemoveForeignKeySponsor', 6),
('CreateTestTable', 'UNDOCreateTestTable', 7)

SELECT * FROM VersionChanged


-- create a table that keeps only the current version (the version is an integer number)

drop TABLE CurrentVersion
CREATE TABLE CurrentVersion
	(currentVersion INT DEFAULT 0)

INSERT INTO CurrentVersion VALUES(0)

--SELECT * FROM CurrentVersion

GO
CREATE OR ALTER PROCEDURE goToVersion(@version INT)
AS
BEGIN
	DECLARE @currentVersion INT
	IF @version < 0 OR @version > 7   -- check if the parameter is ok
		BEGIN
			RAISERROR('Version number must be smaller than 7 and greater or equal to 0!',17,1)
			RETURN
		END
	ELSE
		IF @version = @currentVersion -- check whether the version parameter is the current parameter
			BEGIN
				PRINT N'We are already on this version!'
				RETURN
			END
		ELSE
		DECLARE @currentProcedure NVARCHAR(50)
		SET @currentVersion = (SELECT currentVersion FROM CurrentVersion)  -- get the current version of the database
		IF @currentVersion < @version
			BEGIN
				WHILE @currentVersion < @version
					BEGIN
						PRINT N'We are at version ' + CAST(@currentVersion as NVARCHAR(10))

						SET @currentProcedure = (SELECT currentProcedure
												FROM VersionChanged
												WHERE versionTO = @currentVersion + 1)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion + 1
					END
			END
		ELSE 
		IF @currentVersion > @version
			BEGIN
				WHILE @currentVersion > @version
					BEGIN
						PRINT N'We are at version ' + CAST(@currentVersion as NVARCHAR(10))

						SET @currentProcedure = (SELECT backwardsProcedure
												FROM VersionChanged
												WHERE versionTO = @currentVersion)
						EXEC(@currentProcedure)
						SET @currentVersion = @currentVersion - 1

					END
			END
		UPDATE CurrentVersion
			SET currentVersion = @currentVersion
		PRINT N'Current version updated!'
		PRINT N'We reached the desired version: ' + CAST(@currentVersion as NVARCHAR(10))
END

Select * FROM VersionChanged

GO
EXEC goToVersion 3
EXEC goToVersion 7
EXEC goToVersion 5
EXEC goToVersion 2
EXEC goToVersion 0
EXEC goToVersion -1