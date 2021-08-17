---@class UserWidget
local attwidget = {}

function attwidget:Initialize()
end

function attwidget:RemoveAttachmentFromSlot()
    if (self.AttachmentItem ~= nil) then
        local mypc = self:GetOwningPlayer()
        local backpack = mypc.MyBackPack
        backpack:RemovefromAttachmentSlot(self.SlotId)
    end
end

function attwidget:DropAttachmentFromSlot()
    if (self.AttachmentItem ~= nil) then
        local mypc = self:GetOwningPlayer()
        local backpack = mypc.MyBackPack
        backpack:RemovefromAttachmentSlot(self.SlotId)
        backpack:DropItem(self.AttachmentItem.ItemTypeId,1)

    end
end


return attwidget