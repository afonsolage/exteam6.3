/****** Object:  StoredProcedure [dbo].[GensRewardCheck]    Script Date: 05/31/2014 13:36:38 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO
CREATE Procedure [dbo].[GensRewardCheck]
	@CharacterName	varchar(10)
AS
BEGIN
	DECLARE @Result int
	DECLARE @RewardDate smalldatetime
	
	SET @Result = 0
	
	SET NOCOUNT ON
	SELECT @RewardDate = RewardDate FROM GensMember WHERE Name = @CharacterName
	
	IF( DateAdd(dd, 1, @RewardDate) < GetDate() )
	BEGIN
		SET @Result = 1
	END
	
	SELECT @Result
	
	SET NOCOUNT OFF	
END

