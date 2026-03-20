local valid = 0

for line in io.lines("./input.txt") do
	local t = {}

	for n in line:gmatch("%d+") do
		t[#t + 1] = tonumber(n)
	end

	if #t == 3 then
		table.sort(t)
		local a, b, c = t[1], t[2], t[3]

		if a + b > c then
			valid = valid + 1
		end
	end
end

print(valid)

