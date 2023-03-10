
/****** Object:  StoredProcedure [dbo].[WZ_MACROINFO_SAVE]    Script Date: 09/12/2014 17:46:21 ******/
SET ANSI_NULLS OFF
GO
SET QUOTED_IDENTIFIER OFF
GO






CREATE   PROCEDURE [dbo].[WZ_MACROINFO_SAVE] 
	@AccountID 	 VARCHAR(10),
	@Name	  	 VARCHAR(10),
              @MacroInfo	 VARBINARY(256)
AS
	SET NOCOUNT ON

	IF EXISTS (SELECT TOP 1 * FROM T_MacroInfo  WITH (READUNCOMMITTED)
	WHERE AccountID = @AccountID and Name = @Name)
              BEGIN
                    	UPDATE T_MacroInfo SET MacroInfo = @MacroInfo WHERE AccountID = @AccountID and Name = @Name
              END
              ELSE
              BEGIN
	INSERT INTO T_MacroInfo(AccountID, Name, MacroInfo) VALUES(@AccountID, @Name, @MacroInfo)
              END
       

	
	SET NOCOUNT OFF




