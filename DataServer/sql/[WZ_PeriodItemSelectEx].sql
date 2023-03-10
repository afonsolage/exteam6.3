USE [MuOnline6]
GO
/****** Object:  StoredProcedure [dbo].[WZ_PeriodItemSelectEx]    Script Date: 08/16/2014 19:05:28 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE  Procedure [dbo].[WZ_PeriodItemSelectEx]

	@UserGuid		int,
	@CharacterName	varchar(10)
AS
BEGIN
	DECLARE @ErrorCode int
	DECLARE @ItemInfoCount int
	DECLARE @PeriodIndex int
	DECLARE @ExpireDate smalldatetime
	DECLARE @UsedInfo tinyint

	SET @PeriodIndex = 0
	SET @ErrorCode = 0
	SET @ItemInfoCount = 0
	SET @UsedInfo = 0

	SET NOCOUNT ON
	DECLARE CUR CURSOR FOR SELECT [PeriodIndex] FROM PeriodItemEx WHERE UserGuid = @UserGuid AND Name = @CharacterName FOR UPDATE

	OPEN CUR

	FETCH NEXT FROM CUR INTO @PeriodIndex
	WHILE( @@fetch_status <> -1 )
	BEGIN
		/*IF( @@fetch_status <> -2 )
		BEGIN
			IF( @ExpireDate < GetDate() )
			BEGIN
				UPDATE T_PeriodItem_Info SET UsedInfo = 0 WHERE PeriodIndex = @PeriodIndex
			END
		END*/
		FETCH NEXT FROM CUR INTO @PeriodIndex/*, @ExpireDate, @UsedInfo*/
	END

	SELECT * FROM PeriodItemEx where UserGuid = @UserGuid AND Name = @CharacterName
	IF( @@Error <> 0 )
	BEGIN
		SET @ErrorCode = -1
	END

	CLOSE CUR
	DEALLOCATE CUR

	SET NOCOUNT OFF
END
