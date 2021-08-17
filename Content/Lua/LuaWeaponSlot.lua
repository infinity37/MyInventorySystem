---@class UserWidget
local weaponslot = {}
function weaponslot:Initialize()

end

function weaponslot:LoadWeaponSlot()
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    self.WeaponWidget1.WeaponItem = backpack.WeaponSlot:Get(0)
    self.WeaponWidget2.WeaponItem = backpack.WeaponSlot:Get(1)
end


function weaponslot:LoadAttachmentSlot()
    local mypc = self:GetOwningPlayer()
    local backpack = mypc.MyBackPack
    
    self.AttachmentWidget1.AttachmentItem = backpack.AttachmentSlot:Get(0)
    self.AttachmentWidget2.AttachmentItem = backpack.AttachmentSlot:Get(1)
    self.AttachmentWidget3.AttachmentItem = backpack.AttachmentSlot:Get(2)
    self.AttachmentWidget4.AttachmentItem = backpack.AttachmentSlot:Get(3)
end


return weaponslot