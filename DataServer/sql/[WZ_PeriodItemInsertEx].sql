/****** Object:  StoredProcedure [dbo].[WZ_PeriodItemInsertEx]    Script Date: 08/16/2014 19:05:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[WZ_PeriodItemInsertEx]
	@UserGuid			int,
	@CharacterName		varchar(10),
	@ItemType			tinyint,
	@ItemCode			int,
	@EffectCategory		tinyint,
	@EffectType1		tinyint,
	@EffectType2		tinyint,
	@Serial				bigint,
	@Duration			int,
	@BuyDate			bigint,
	@ExpireDate			bigint
	AS
BEGIN
	DECLARE @ErrorCode int
	DECLARE @PeriodItemIndex int

	SET @ErrorCode = 0
	SET @PeriodItemIndex = 0

	SET XACT_ABORT ON
	SET NOCOUNT ON

	BEGIN TRANSACTION

	SELECT  @PeriodItemIndex = PeriodIndex FROM PeriodItemEx WHERE UserGuid = @UserGuid AND Name = @CharacterName AND ItemCode = @ItemCode AND ItemType = @ItemType AND OptionType = @EffectCategory AND ItemType != 2

	IF ( @PeriodItemIndex != 0 )
	BEGIN
		DELETE FROM PeriodItemEx WHERE UserGuid = @UserGuid AND Name = @CharacterName AND ItemCode = @ItemCode AND ItemType = @ItemType AND OptionType = @EffectCategory
	END

	INSERT INTO PeriodItemEx (UserGuid, Name, ItemType, ItemCode, EffectType1, EffectType2, OptionType, SerialCode, Duration, BuyDateConvert, ExpireDateConvert) VALUES
	( @UserGuid, @CharacterName, @ItemType, @ItemCode, @EffectType1, @EffectType2, @EffectCategory, @Serial, @Duration, @BuyDate, @ExpireDate)
	IF( @@Error <> 0 )
	BEGIN
		SET @ErrorCode = 2
	END

	IF ( @ErrorCode  <> 0 )
		ROLLBACK TRANSACTION
	ELSE
		COMMIT TRANSACTION

	SELECT @ErrorCode

	SET NOCOUNT OFF
	SET XACT_ABORT OFF
END
