/****** Object:  StoredProcedure [dbo].[WZ_LuckyItemInsert]    Script Date: 08/16/2014 19:04:10 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****************************************************************
TITLE    :	钒虐酒捞袍 积己

EX       :	WZ_LuckyItemInsert

PROJECT  :	Season 6

CALL     : 

INPUT    : 

OUTPUT   :	@ErrorCode 
			0 : 己傍
			2 : 角菩

REVERSION:
-------------------------------------------------------------------
DATE		Author				Description		
-------------------------------------------------------------------
2010-09-16	傍饶琶[MU_STUDIO]	弥檬 累己
2011-04-14	C.H.O				@DurabilitySmall tinyint -> smallint
-------------------------------------------------------------------	
*****************************************************************/
CREATE PROC  [dbo].[WZ_LuckyItemInsert]  
@UserGuid 			int
,@CharName			varchar(10)
,@ItemCode			int
,@ItemSerial		bigint
,@DurabilitySmall	smallint
AS         
DECLARE @ErrorCode int        
SET	@ErrorCode = 0        

SET NOCOUNT ON    
SET	XACT_ABORT ON
        
BEGIN TRAN

-- -----------------------------------------------------------------
-- 沥焊啊 绝促搁....        
-- -----------------------------------------------------------------
IF NOT EXISTS (SELECT ItemCode FROM T_LUCKY_ITEM_INFO  WITH ( READUNCOMMITTED )         
WHERE CharName = @CharName AND ItemCode = @ItemCode AND ItemSerial  = @ItemSerial
and	UserGuid = @UserGuid)
BEGIN            
	INSERT INTO T_LUCKY_ITEM_INFO (UserGuid, CharName, ItemCode, ItemSerial, DurabilitySmall) 
	VALUES  (@UserGuid, @CharName, @ItemCode, @ItemSerial, @DurabilitySmall)    
END       

-- ----------------------------------------------------------------- 
--沥焊啊 乐促搁 盎脚
-- -----------------------------------------------------------------
ELSE        
BEGIN    
	UPDATE T_LUCKY_ITEM_INFO 
	SET	DurabilitySmall = @DurabilitySmall
	WHERE CharName = @CharName AND ItemCode = @ItemCode AND ItemSerial  = @ItemSerial 
	and	UserGuid = @UserGuid
END        

IF( @@Error <> 0 )        
BEGIN        
SET @ErrorCode = 2        
END        

IF ( @ErrorCode  <> 0 ) 
ROLLBACK TRAN       
ELSE        
COMMIT TRAN

SELECT @ErrorCode        

SET	XACT_ABORT OFF        
SET NOCOUNT OFF

