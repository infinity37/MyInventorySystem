---@class UserWidget
local baseinfo = {}
function baseinfo:Initialize()

end

function baseinfo:GetPercent0()
    local player = self:GetOwningPlayerPawn()
    local percent = player.CurrentHealth/player.MaxHealth
    return percent
end

function baseinfo:GetPercent1()
    local player = self:GetOwningPlayerPawn()
    local percent = player.Energy/player.MaxEnergy
    return percent
end

function baseinfo:GetText0()
    local player = self:GetOwningPlayerPawn()
    return tostring(math.floor(player.Damage * player.DamageMul))
end

return baseinfo