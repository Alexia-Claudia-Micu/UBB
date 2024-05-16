use Yelp_Reviews
GO
SET NOCOUNT ON;
IF EXISTS (SELECT [name] FROM sys.objects 
            WHERE object_id = OBJECT_ID('RandIntBetween'))
BEGIN
   DROP FUNCTION RandIntBetween;
END
GO

CREATE FUNCTION RandIntBetween(@lower INT, @upper INT, @rand FLOAT)
RETURNS INT
AS
BEGIN
  DECLARE @result INT;
  DECLARE @range INT = @upper - @lower + 1;
  SET @result = FLOOR(@rand * @range + @lower);
  RETURN @result;
END
GO

CREATE OR ALTER PROC deleteData
@table_id INT
AS
BEGIN
	print('------------------------------------------------ HERE 2')
	DECLARE @table_name NVARCHAR(50) = (
		SELECT [Name] FROM [Tables] WHERE TableID = @table_id
	)

	DECLARE @function NVARCHAR(MAX)
	SET @function = N'DELETE FROM ' + @table_name
	PRINT @function
	EXEC sp_executesql @function
END
GO

CREATE OR ALTER PROC deleteDataFromAllTables
@test_id INT
AS
BEGIN
	DECLARE @tableID INT
	DECLARE cursorForDelete cursor local for
		SELECT TT.TableID
		FROM TestTable TT
			INNER JOIN Tests T ON TT.TestID = T.TestID
		WHERE T.TestID = @test_id
		ORDER BY TT.Position DESC

	OPEN cursorForDelete
	FETCH cursorforDelete INTO @tableID
	WHILE @@FETCH_STATUS = 0
	BEGIN
		exec deleteData @tableID

		FETCH NEXT FROM cursorForDelete INTO @tableID
	END
	CLOSE cursorForDelete
END
GO

drop procedure insertDataIntoAd

CREATE OR ALTER PROC insertDataIntoPerson
@nrOfRows INT,
@tableName VARCHAR(50)
AS
BEGIN
    DECLARE @FN VARCHAR(20)
    DECLARE @LN VARCHAR(20)
    DECLARE @BD DATE
    DECLARE @ADDR VARCHAR(100)
    DECLARE @ST VARCHAR(20)
	DECLARE @S VARCHAR(20)
	DECLARE @SN INT
    DECLARE @StartDate DATE = '1970-01-01'
    DECLARE @EndDate DATE = '2004-01-01'

    WHILE @nrOfRows > 0
    BEGIN
        SET @FN = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Ana', 'Maria', 'Ion', 'Radu'))
        WHILE @FN IS NULL
        BEGIN
            SET @FN = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Ana', 'Maria', 'Ion', 'Radu'))
        END

        SET @LN = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Pop', 'Muntean', 'Muresan', 'Raducan'))
        WHILE @LN IS NULL
        BEGIN
            SET @LN = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Pop', 'Muntean', 'Muresan', 'Raducan'))
        END

        SET @ST = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Calea ', 'Strada ', 'Bulevardul '))
        WHILE @ST IS NULL
        BEGIN
            SET @ST = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Calea ', 'Strada ', 'Bulevardul '))
        END

		SET @S = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Plopului, nr.  ', 'Decembrie, nr.  ', 'Stajarului, nr.  '))
        WHILE @S IS NULL
        BEGIN
            SET @S = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Plopului, nr.  ', 'Decembrie, nr.  ', 'Stajarului, nr.  '))
        END

		SET @SN = [dbo].[RandIntBetween](1,500,Rand())

        SET @ADDR = @ST + @S + CAST(@SN AS NVARCHAR(4))

        DECLARE @RandomDays INT = ROUND(RAND() * DATEDIFF(day, @StartDate, @EndDate), 0)
        SET @BD = DATEADD(day, @RandomDays, @StartDate)

        -- Explicitly specify column names in the INSERT statement
        INSERT INTO PERSON (FirstName, LastName, BirthDate, Address) VALUES (@FN, @LN, @BD, @ADDR)

        SET @nrOfRows = @nrOfRows - 1
    END
END
GO


CREATE OR ALTER PROC insertDataIntoDepartment
@nrOfRows INT,
@tableName VARCHAR(50)
AS
BEGIN
	DECLARE @N VARCHAR(50)

    WHILE @nrOfRows > 0
    BEGIN
        SET @N = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Sales','Human Resources','Finance','Accounting','Marketing','Research and Development','Product Management','Engeneering','Corporate Communication','Purchasing','Procurment','Costumer Service','Lead'))
        WHILE @N IS NULL
        BEGIN
            SET @N = (SELECT CHOOSE(CAST(RAND() * 10 + 1 AS INT), 'Sales','Human Resources','Finance','Accounting','Marketing','Research and Development','Product Management','Engeneering','Corporate Communication','Purchasing','Procurment','Costumer Service','Lead'))
        END

		IF NOT EXISTS (SELECT * FROM Department WHERE DepartmentName = @N)
		BEGIN
			INSERT INTO Department (DepartmentName) values (@N);
			SET @nrOfRows = @nrOfRows - 1;
		END
    END
END
GO


CREATE OR ALTER PROC insertDataIntoService_Business
@nrOfRows INT,
@tableName VARCHAR(50)
AS
BEGIN
	DECLARE @S INT
	DECLARE @B INT

    WHILE @nrOfRows > 0
    BEGIN
        SET @S = [dbo].[RandIntBetween](1,(select count(*) from Servicee),Rand())
		SET @B = [dbo].[RandIntBetween](1,(select count(*) from Business),Rand())

		IF NOT EXISTS (SELECT * FROM Service_Business WHERE Business = @B AND Service = @S)
		BEGIN
			INSERT INTO Service_Business (Service, Business) VALUES (@S, @B);
			SET @nrOfRows = @nrOfRows - 1;
		END
    END
END
GO

CREATE OR ALTER PROC insertDataIntoReview
@nrOfRows INT,
@tableName VARCHAR(50)
AS
BEGIN
	DECLARE @B INT
	DECLARE @U INT
	DECLARE @R INT

    WHILE @nrOfRows > 0
    BEGIN
        SET @B = [dbo].[RandIntBetween](1,(select count(*) from Business),Rand())
		SET @U = [dbo].[RandIntBetween](1,(select count(*) from Users),Rand())
		SET @R = [dbo].[RandIntBetween](1,5,Rand())
        INSERT INTO Review (Business, Users, Rating, Comment) VALUES (@B, @U, @R, '')
        SET @nrOfRows = @nrOfRows - 1
    END
END
GO

CREATE OR ALTER VIEW Departments
AS
	SELECT *
	FROM Department
GO


-- a view with a SELECT statement operating on at least 2 tables
-- Selects the names of sponsors and the companies they sponsor
CREATE OR ALTER VIEW SponsorsAndWhoTheySponsor
AS
	select distinct pid, FirstName, LastName, b1.Title
	from Person p1
	inner join Sponsors s1 on p1.pid = s1.person
	inner join Business b1 on s1.business = b1.bid
GO

-- a view with a SELECT statement that has a GROUP BY clause and operates on at least 2 tables
-- 
CREATE OR ALTER VIEW averageSalaryForEachBusiness
AS
	SELECT b.bid, AVG(e.Salary) as AverageSalary
	FROM Business b INNER JOIN Employee e
		ON b.bid= e.Business
	GROUP BY b.bid
	HAVING 1 < count(e.eid)
GO

CREATE OR ALTER PROC insertData
@testRunID INT,
@testID INT,
@tableID INT
AS
BEGIN
	--starting time before test runs
	DECLARE @startTime DATETIME = SYSDATETIME()

	-- we get the name of the table based on the tableID
	DECLARE @tableName VARCHAR(50) = (
		SELECT [Name] FROM [Tables] WHERE TableID = @tableID
	)

	PRINT 'Insert data into table ' + @tableName

	-- we get the number of rows we have to insert based on the tableID and on the testID
	DECLARE @nrOfRows INT = (
		SELECT [NoOfRows] FROM TestTable  
			WHERE TestID = @testID AND TableID = @tableID
	)
	if @tableName = 'Department'
		EXEC insertDataIntoDepartment @nrOfRows, @tableName
	
	else if @tableName = 'Service_Business'
		EXEC insertDataIntoService_Business @nrOfRows, @tableName
	
	else if @tableName = 'Review'
		EXEC insertDataIntoReview @nrOfRows, @tableName
		
	-- we get the end time of the test
	DECLARE @endTime DATETIME = SYSDATETIME()

	-- we insert the performance
	INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt)
		VALUES (@testRunID, @tableID, @startTime, @endTime)

END
GO

CREATE OR ALTER PROCEDURE insertDataIntoAllTables
@testRunID INT,
@testID INT
AS
BEGIN
	DECLARE @tableID INT
	DECLARE cursorForInsert CURSOR LOCAL FOR
		SELECT TableID
		FROM TestTable TT
			INNER JOIN Tests T on TT.TestID = T.TestID
		WHERE T.TestID = @testID
		ORDER BY TT.Position ASC
	
	OPEN cursorForInsert
	FETCH cursorForInsert INTO @tableID
	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC insertData @testRunID, @testID, @tableID

		FETCH NEXT FROM cursorForInsert INTO @tableID
	END
	CLOSE cursorForInsert
END
GO

CREATE OR ALTER PROC selectDataView
@viewID INT,
@testRunID INT
AS
BEGIN
	-- starting time before test runs
	DECLARE @startTime DATETIME = SYSDATETIME()

	DECLARE @viewName VARCHAR(100) = (
		SELECT [Name] FROM [Views]
			WHERE ViewID = @viewID
	)

	PRINT 'Selecting from view ' + @viewName

	DECLARE @query NVARCHAR(200) = N'SELECT * FROM '  + @viewName
	EXEC sp_executesql @query

	-- ending time after test
	DECLARE @endTime DATETIME = SYSDATETIME()

	INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt)
		VALUES(@testRunID, @viewID, @startTime, @endTime)

END
GO

CREATE OR ALTER PROC selectDataFromAllViews
@testRunID INT,
@testID INT
AS
BEGIN
	PRINT 'Select all view for test = ' + convert(VARCHAR, @testID)

	DECLARE @viewID INT

	DECLARE cursorForViews CURSOR LOCAL FOR
		SELECT TV.ViewID FROM TestViews TV
			INNER JOIN Tests T on T.TestID = TV.TestID
		WHERE TV.TestID = @testID

	OPEN cursorForViews
	FETCH cursorForViews INTO @viewID
	WHILE @@FETCH_STATUS = 0
	BEGIN
		-- We select the view
		EXEC selectDataView @viewID, @testRunID
		FETCH NEXT FROM cursorForViews INTO @viewID
	END
	CLOSE cursorForViews
END
GO


CREATE OR ALTER PROC runTest
@testID INT,
@description VARCHAR(5000)
AS
BEGIN
	PRINT 'Running test with id: ' + CONVERT(VARCHAR, @testID) + ' with description: ' + @description

	-- We create a test run
	INSERT INTO TestRuns([Description]) values (@description)

	-- Get the current testRunID
	DECLARE @testRunID INT = (SELECT MAX(TestRunID) FROM TestRuns)

	-- Get the starting time before the test runs
	DECLARE @startTime DATETIME = SYSDATETIME()
	EXEC deleteDataFromAllTables @testID
	EXEC insertDataIntoAllTables @testRunID, @testID
	EXEC selectDataFromAllViews @testRunID, @testID
	DECLARE @endTIME DATETIME = SYSDATETIME()

	-- Now we update the start time and the end time for the entire RUN
	UPDATE [TestRuns] SET StartAt = @startTime, EndAt = @endTIME

	-- Compute the total number of seconds the test took
	DECLARE @totalTime INT = DATEDIFF(SECOND, @startTime, @endTime)

	PRINT 'Test with id = ' + CONVERT(VARCHAR, @testID) + ' took ' + CONVERT(VARCHAR, @totalTime) + ' seconds to execute !'

END
GO


CREATE OR ALTER PROC runAllTests
AS
BEGIN
	DECLARE @testName VARCHAR(50)
	DECLARE @testID INT

	DECLARE cursorForTests CURSOR LOCAL FOR
		SELECT * FROM Tests

	OPEN cursorForTests
	FETCH cursorForTests INTO @testID, @testName
	WHILE @@FETCH_STATUS = 0
	BEGIN
		PRINT 'Running ' + @testName + ' with id: ' + CONVERT(VARCHAR, @testID)

		-- Now we run the test
		EXEC runTest @testID, ' perfect ;P'

		FETCH NEXT FROM cursorForTests INTO @testID, @testName
	END
	CLOSE cursorForTests
END
GO

INSERT INTO Tables (Name) Values ('Department'),('Service_Business'),('Review')

INSERT INTO Tests(Name) Values('Test 1'), ('Test 2')

INSERT INTO TestTable(TestID, TableID, NoOfRows, Position) VALUES 
	(1,1,18,6),
	(1,2,14,5),
	(2,1,14,3),
	(1,3,31,1),
	(2,3,31,1)

INSERT INTO TestTable(TestID, TableID, NoOfRows, Position) VALUES (1,1,5,1)

INSERT INTO Views(Name) VALUES ('Departments'),('SponsorsAndWhoTheySponsor'),('averageSalaryForEachBusiness')


INSERT INTO TestViews (TestID, ViewID) VAlUES(1,1),(2,1),(2,2),(2,3)

EXEC runTest 1, 'does it work'
EXEC runAllTests

SELECT * FROM TestRunTables
SELECT * FROM TestRuns
SELECT * FROM TestRunViews

delete from TestRunTables
delete from TestRuns
delete from TestRunViews