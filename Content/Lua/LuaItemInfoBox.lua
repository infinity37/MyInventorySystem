---@class UserWidget
local iteminfo = {}
local GameplayStatics=import'GameplayStatics';

function iteminfo:Initialize()
end

function iteminfo:GetDisplayDamage()
    local itemtype = math.modf(self.ItemInfo.ItemTypeId/100)
    if (itemtype == 5) then
        return tostring("Damage：")
    else
        return tostring("")
    end
end

function iteminfo:GetDamage()
    local itemtype = math.modf(self.ItemInfo.ItemTypeId/100)
    if (itemtype == 5) then
        return tostring(self.ItemInfo.Damage)
    else
        return tostring("")
    end
end

function iteminfo:GetDisplayAmmo()
    local itemtype = math.modf(self.ItemInfo.ItemTypeId/100)
    if (itemtype == 5) then
        return tostring("AmmoType：")
    else
        return tostring("")
    end
end

function iteminfo:GetAmmoType()
    local itemtype = math.modf(self.ItemInfo.ItemTypeId/100)
    if (itemtype == 5) then
        local ammotypeid = self.ItemInfo.AmmoType
        local gamestate = GameplayStatics.GetGameState(self)
        local infotable = gamestate:GetItemInfoTable()
        local ammoitem = infotable:GetItemInfoById(ammotypeid)
        return tostring(ammoitem.ItemName)
    else
        return tostring("")
    end
end

return iteminfo