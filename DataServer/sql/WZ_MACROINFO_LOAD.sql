
/****** Object:  StoredProcedure [dbo].[WZ_MACROINFO_LOAD]    Script Date: 09/12/2014 17:47:11 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO







CREATE    PROCEDURE [dbo].[WZ_MACROINFO_LOAD] 
	@AccountID 	 VARCHAR(10),
	@Name	  	 VARCHAR(10)
AS
	SET NOCOUNT ON

	SELECT TOP 1 MacroInfo FROM T_MacroInfo where AccountID = @AccountID and Name = @Name
	
	SET NOCOUNT OFF





