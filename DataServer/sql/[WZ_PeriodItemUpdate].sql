USE [MuOnline6]
GO
/****** Object:  StoredProcedure [dbo].[WZ_PeriodItemUpdate]    Script Date: 08/16/2014 19:05:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE Procedure [dbo].[WZ_PeriodItemUpdate]

	@UserGuid		int,
	@CharacterName 	varchar(10),
	@ItemCode		int,
	@UsedTime		int,
	@LeftTime		int
AS
BEGIN
	DECLARE @ErrorCode int
	DECLARE @ItemInfoCount int
	DECLARE @RetLeftTime int

	SET @ErrorCode = 0
	SET @ItemInfoCount = 0
	SET @RetLeftTime = 0

	SET XACT_ABORT ON
	SET NOCOUNT ON

	BEGIN TRANSACTION

	SELECT @ItemInfoCount = COUNT(*) FROM T_PeriodItem_Info where UserGuid = @UserGuid AND CharacterName = @CharacterName AND UsedInfo = 1

	IF( @ItemInfoCount <> 1 )
	BEGIN
		SET @ErrorCode = 1
	END
	ELSE
	BEGIN
		UPDATE T_PeriodItem_Info SET UsedTime = UsedTime + @UsedTime, LeftTime = @LeftTime WHERE UserGuid = @UserGuid AND CharacterName = @CharacterName AND ItemCode = @ItemCode AND UsedInfo = 1
		IF( @@Error <> 0 )
		BEGIN
			SET @ErrorCode = 2
		END
	END

	SELECT @RetLeftTime = LeftTime FROM T_PeriodItem_Info where UserGuid = @UserGuid AND CharacterName = @CharacterName AND ItemCode = @ItemCode AND UsedInfo = 1
	IF ( @RetLeftTime <= 0 )
	BEGIN
		UPDATE T_PeriodItem_Info SET UsedInfo = 0, LeftTime = 0 WHERE UserGuid = @UserGuid AND CharacterName = @CharacterName AND ItemCode = @ItemCode AND UsedInfo = 1
		SET @ErrorCode = 3
	END

	IF ( @ErrorCode  <> 0  AND @ErrorCode <> 3 )
		ROLLBACK TRANSACTION
	ELSE
		COMMIT TRANSACTION

	SELECT @ErrorCode

	SET NOCOUNT OFF
	SET XACT_ABORT OFF
END
