local current = { x = 2, y = 2 }
local pad = {
	{ 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 9 },
}

local function clamp(val, min, max)
	if val < min then
		return min
	end
	if val > max then
		return max
	end
	return val
end

for line in io.lines("./input.txt") do
	for i = 1, #line do
		local char = line:sub(i, i)

		if char == "U" then
			current.x = clamp(current.x - 1, 1, #pad)
		elseif char == "D" then
			current.x = clamp(current.x + 1, 1, #pad)
		elseif char == "L" then
			current.y = clamp(current.y - 1, 1, #pad[1])
		elseif char == "R" then
			current.y = clamp(current.y + 1, 1, #pad[1])
		end
	end

	print(pad[current.x][current.y])
end

