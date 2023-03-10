/****** Object:  StoredProcedure [dbo].[WZ_PeriodItemDeleteEx]    Script Date: 08/16/2014 19:04:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE Procedure [dbo].[WZ_PeriodItemDeleteEx]

	@UserGuid		int,
	@CharacterName	varchar(10),
	@ItemCode		int,
	@ItemType		tinyint,
	@Serial			bigint
AS
BEGIN
	DECLARE @ErrorCode int
	DECLARE @ItemInfoCount int

	SET @ErrorCode = 0
	SET @ItemInfoCount = 0

	SET NOCOUNT ON

	SELECT @ItemInfoCount = COUNT(*) FROM PeriodItemEx where UserGuid = @UserGuid AND Name = @CharacterName AND ItemCode = @ItemCode AND ItemType = @ItemType AND SerialCode = @Serial

	IF( @ItemInfoCount < 1 )
	BEGIN
		SET @ErrorCode = 1
	END

	IF( @ErrorCode <> 1 )
	BEGIN
		DELETE FROM PeriodItemEx WHERE UserGuid = @UserGuid AND Name = @CharacterName AND ItemCode = @ItemCode AND ItemType = @ItemType AND SerialCode = @Serial
	END

	SELECT @ErrorCode

	SET NOCOUNT OFF
END
