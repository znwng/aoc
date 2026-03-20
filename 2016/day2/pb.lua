local current = { x = 3, y = 1 }
local pad = {
	{ nil, nil, "1", nil, nil },
	{ nil, "2", "3", "4", nil },
	{ "5", "6", "7", "8", "9" },
	{ nil, "A", "B", "C", nil },
	{ nil, nil, "D", nil, nil },
}

local function is_valid(x, y)
	return pad[x] and pad[x][y] ~= nil
end

for line in io.lines("./input.txt") do
	for i = 1, #line do
		local char = line:sub(i, i)

		local new_x, new_y = current.x, current.y

		if char == "U" then
			new_x = current.x - 1
		elseif char == "D" then
			new_x = current.x + 1
		elseif char == "L" then
			new_y = current.y - 1
		elseif char == "R" then
			new_y = current.y + 1
		end

		if is_valid(new_x, new_y) then
			current.x = new_x
			current.y = new_y
		end
	end

	io.write(pad[current.x][current.y])
end

print()

