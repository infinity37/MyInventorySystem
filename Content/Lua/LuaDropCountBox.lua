---@class UserWidget
local dcbox={}
---local KML = import("KismetMathLibrary")

function dcbox:Initialize()
end

function dcbox:Construct()
    local spinbox = self.DropCount
    spinbox:SetMaxValue(self.ItemInfo.ItemCount)
    spinbox:SetMaxSliderValue(self.ItemInfo.ItemCount)
end

function dcbox:ConfirmDrop()
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    local count = self.DropCount:GetValue()
    backpack:DropItem(self.ItemInfo.ItemTypeId, math.floor(count))
    local mypl = self:GetOwningPlayerPawn()
    mypl:RefreshBagUI()
    self:RemoveFromParent()
end

return dcbox