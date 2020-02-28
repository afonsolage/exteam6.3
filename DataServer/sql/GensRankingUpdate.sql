/****** Object:  StoredProcedure [dbo].[GensRankingUpdate]    Script Date: 05/31/2014 13:22:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
CREATE PROCEDURE [dbo].[GensRankingUpdate] (@Influence int)
AS
SET NOCOUNT ON
	DECLARE _Cursor CURSOR FOR
	SELECT Name FROM GensMember WHERE Influence = @Influence AND Contribute >= 10000 order by Contribute desc
     
  	DECLARE @TempName  varchar(10), @TempRank int
   	SET @TempRank = 1
     
    	OPEN _Cursor;
    	FETCH NEXT FROM _Cursor INTO @TempName
    	WHILE @@FETCH_STATUS = 0
     
    		BEGIN
    			UPDATE GensMember SET Rank = @TempRank WHERE Name = @TempName AND Influence = @Influence;
    			SET @TempRank = @TempRank + 1;
    			FETCH NEXT FROM _Cursor INTO @TempName
    		END;

 	CLOSE _Cursor;
 	DEALLOCATE _Cursor;
SET NOCOUNT OFF