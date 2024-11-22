--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_LuaController_C
local M = UnLua.Class()

function M:Initialize(Initializer)
    print('BP_LuaController_initialized')
end

-- function M:UserConstructionScript()
-- end

function M:ReceiveBeginPlay()
    print('BP_LuaController Received BeginPlay')
    -- show mouse
    self.bShowMouseCursor = true
end

-- function M:ReceiveEndPlay()
-- end

function M:ReceiveTick(DeltaSeconds)
    local pawn = self:K2_GetPawn()
    if pawn then
        local HitResult = UE.FHitResult()
        if self:GetHitResultUnderCursor(UE.ECollisionChannel.ECC_Visibility, true, HitResult) then
            local TargetLocation = HitResult.location
            local Location = pawn:K2_GetActorLocation()
            local Difference = UE.FVector(
                    TargetLocation.X - Location.X,
                    TargetLocation.Y - Location.Y,
                    TargetLocation.Z - Location.Z
            )
            pawn:AddMovementInput(Difference, 1.0, false)
            Difference.Z = 0
            local rotation = Difference:ToRotator()
            pawn:K2_AddActorWorldRotation(rotation, false, nil, false)
        end
    end
end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

return M
