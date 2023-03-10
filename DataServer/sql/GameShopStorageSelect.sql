/****** Object:  StoredProcedure [dbo].[GameShopStorageSelect]    Script Date: 08/16/2014 19:01:04 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO


CREATE Procedure [dbo].[GameShopStorageSelect]
	@AccountID	varchar(10)
AS
BEGIN
	DECLARE @ErrorCode int
	DECLARE @Index int

	SET @Index = 0
	SET @ErrorCode = 0

	SET NOCOUNT ON
	DECLARE CUR CURSOR FOR SELECT [Index] FROM GameShopStorage WHERE AccountID = @AccountID FOR UPDATE

	OPEN CUR

	FETCH NEXT FROM CUR INTO @Index
	WHILE( @@fetch_status <> -1 )
	BEGIN
		FETCH NEXT FROM CUR INTO @Index
	END

	SELECT * FROM GameShopStorage where AccountID = @AccountID
	IF( @@Error <> 0 )
	BEGIN
		SET @ErrorCode = -1
	END

	CLOSE CUR
	DEALLOCATE CUR

	SET NOCOUNT OFF
END


